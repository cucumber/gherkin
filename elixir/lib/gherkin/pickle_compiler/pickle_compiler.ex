defmodule CucumberGherkin.PickleCompiler do
  @moduledoc false
  defstruct id_gen: nil, pickles: [], language: nil, uri: nil

  alias CucumberMessages.Feature, as: FeatureMessage
  alias CucumberMessages.Scenario, as: ScenarioMessage
  alias CucumberMessages.Step, as: StepMessage
  alias CucumberMessages.TableRow, as: TableRowMessage
  alias CucumberMessages.Pickle, as: PickleMessage
  alias CucumberMessages.PickleStep, as: PickleStepMessage
  alias CucumberMessages.PickleStepArgument, as: PickleStepArgumentMessage
  alias CucumberMessages.PickleTag, as: PickleTagMessage
  alias CucumberMessages.Tag, as: TagMessage
  alias CucumberMessages.FeatureChild, as: FeatureChildMessage
  alias CucumberMessages.Rule, as: RuleMessage
  alias CucumberMessages.Examples, as: ExampleMessage
  alias CucumberMessages.PickleTable, as: PickleTableMessage

  alias CucumberMessages.PickleTableCell, as: PickleTableCellMessage

  alias CucumberMessages.PickleTableRow, as: PickleTableRowMessage
  alias CucumberMessages.DataTable, as: DataTableMessage
  alias CucumberMessages.DocString, as: DocStringMessage

  @me __MODULE__

  def compile(%CucumberGherkin.AstBuilder{gherkin_doc: gherkin_doc, id_gen: id_generator}, uri) do
    me = %@me{id_gen: id_generator, uri: uri}

    case compile_feature(gherkin_doc.feature, me) do
      %{pickles: pickles} -> pickles
      [] -> []
    end
  end

  defp compile_feature(nil, %@me{pickles: p} = _compiler_acc), do: p

  defp compile_feature(%FeatureMessage{} = f, %@me{} = compiler_acc) do
    meta_info = %{
      feature_backgr_steps: [],
      rule_backgr_steps: [],
      pickles: [],
      feature_tags: f.tags,
      compiler_acc: %{compiler_acc | language: f.language}
    }

    children = if f.children, do: f.children, else: []
    Enum.reduce(children, meta_info, fn child, m_acc ->
      case child do
        %{background: background} when background != nil ->
          %{m_acc | feature_backgr_steps: background.steps}

        %{rule: rule} when rule != nil ->
          compile_rule(m_acc, rule)

        %{scenario: scenario} when scenario != nil ->
          compile_scenario(m_acc, scenario, :feature_backgr_steps)
      end
    end)
  end

  defp compile_rule(meta_info, %RuleMessage{} = r) do
    resetted_meta_info = %{meta_info | rule_backgr_steps: meta_info.feature_backgr_steps}
    rule_tags = meta_info.feature_tags ++ r.tags

    Enum.reduce(r.children, resetted_meta_info, fn
      %FeatureChildMessage{background: bg}, m_acc when bg != nil ->
        %{m_acc | rule_backgr_steps: m_acc.rule_backgr_steps ++ bg.steps}

      %FeatureChildMessage{scenario: s}, m_acc when s != nil ->
        %{m_acc | feature_tags: rule_tags} |> compile_scenario(s, :rule_backgr_steps)
    end)
  end

  # Match for a normal scenario. NOT a scenario outline. NO examples.
  defp compile_scenario(m, %ScenarioMessage{examples: []} = s, feature_or_rule_bg_steps?) do
    {steps, semi_updated_acc, _last_keyword_type} =
      case s.steps do
        [] ->
          {[], m.compiler_acc, "Unknown"}

        list_of_steps ->
          (Map.fetch!(m, feature_or_rule_bg_steps?) ++ list_of_steps)
          |> pickle_steps(m.compiler_acc)
      end

    pickle_tags = [m.feature_tags | s.tags] |> List.flatten() |> pickle_tags()
    {id, updated_compiler_acc} = get_id_and_update_compiler_acc(semi_updated_acc)

    new_msg = %PickleMessage{
      ast_node_ids: [s.id],
      id: id,
      language: m.compiler_acc.language,
      location: s.location,
      name: s.name,
      steps: steps,
      tags: pickle_tags,
      uri: m.compiler_acc.uri
    }

    %{m | pickles: [new_msg | m.pickles], compiler_acc: updated_compiler_acc}
  end

  # When there are examples, it is a scenario outline
  defp compile_scenario(m, %ScenarioMessage{examples: examples} = s, feature_or_rule_bg_steps?) do
    Enum.reduce(examples, m, fn %ExampleMessage{} = example, m_acc ->
      scenario_outline_create_pickles(
        m_acc,
        example,
        s,
        feature_or_rule_bg_steps?,
        example.table_header
      )
    end)
  end

  defp scenario_outline_create_pickles(m, _e, _s, _f_or_bg?, nil), do: m

  defp scenario_outline_create_pickles(m, example, s, f_or_bg?, table_header) do
    Enum.reduce(example.table_body, m, fn value_row, m_acc ->
      {steps, updated_acc, last_keyword_type} =
        case s.steps do
          [] -> {[], m_acc.compiler_acc, "Unknown"}
          _steplist -> Map.fetch!(m_acc, f_or_bg?) |> pickle_steps(m_acc.compiler_acc)
        end

      {updated_steps, updated_acc, _last_keyword_type} =
        Enum.reduce(s.steps, {steps, updated_acc, last_keyword_type}, fn scen_outline_step,
                                                                         {step_acc, c_acc,
                                                                          last_keyword_type} ->
          {newly_created_step, new_c_acc, new_last_keyword_type} =
            pickle_step_creator(
              scen_outline_step,
              table_header.cells,
              value_row,
              c_acc,
              last_keyword_type
            )

          {step_acc ++ [newly_created_step], new_c_acc, new_last_keyword_type}
        end)

      tags = m_acc.feature_tags ++ s.tags ++ example.tags
      pickle_tags = tags |> List.flatten() |> pickle_tags()

      {id, updated_acc} = get_id_and_update_compiler_acc(updated_acc)

      new_msg = %PickleMessage{
        ast_node_ids: [s.id, value_row.id],
        id: id,
        language: m_acc.compiler_acc.language,
        location: value_row.location,
        name: interpolate(s.name, table_header.cells, value_row.cells),
        steps: updated_steps,
        tags: pickle_tags,
        uri: m_acc.compiler_acc.uri
      }

      %{m_acc | pickles: [new_msg | m_acc.pickles], compiler_acc: updated_acc}
    end)
  end

  ####################
  # Helper functions #
  ####################
  defp pickle_tags(list_of_tag_messages), do: Enum.map(list_of_tag_messages, &pickle_tag/1)
  defp pickle_tag(%TagMessage{} = t), do: %PickleTagMessage{ast_node_id: t.id, name: t.name}

  defp pickle_steps(step_messages, %@me{} = acc) do
    {reversed_msges, new_acc, last_keyword_type} =
      Enum.reduce(step_messages, {[], acc, "Unknown"}, fn message,
                                                          {pickle_steps_acc, compiler_acc,
                                                           last_keyword_type} ->
        {pickle_step, updated_acc, updated_last_keyword_type} =
          pickle_step(message, compiler_acc, last_keyword_type)

        {[pickle_step | pickle_steps_acc], updated_acc, updated_last_keyword_type}
      end)

    {Enum.reverse(reversed_msges), new_acc, last_keyword_type}
  end

  defp pickle_step(%StepMessage{} = m, %@me{} = acc, last_keyword_type),
    do: pickle_step_creator(m, [], nil, acc, last_keyword_type)

  defp pickle_step_creator(%StepMessage{} = m, variable_cells, values_row, %@me{} = acc, last_keyword_type) do
    value_cells =
      case values_row do
        nil -> []
        data -> data.cells
      end

    step_text = interpolate(m.text, variable_cells, value_cells)
    {id, updated_compiler_acc} = get_id_and_update_compiler_acc(acc)
    effective_keyword_type = effective_keyword_type(m.keyword_type, last_keyword_type)

    message =
      %PickleStepMessage{
        argument: nil,
        ast_node_ids: [m.id],
        id: id,
        text: step_text,
        type: effective_keyword_type
      }
      |> add_ast_node_id(values_row)
      |> add_datatable(m, variable_cells, value_cells)
      |> add_doc_string(m, variable_cells, value_cells)

    {message, updated_compiler_acc, effective_keyword_type(m.keyword_type, last_keyword_type)}
  end

  defp interpolate(text, variable_cells, value_cells) do
    variable_cells
    |> Enum.zip(value_cells)
    |> Enum.reduce(text, fn {variable_cell, value_cell}, text ->
      String.replace(text, "<#{variable_cell.value}>", value_cell.value)
    end)
  end

  defp pickle_data_table_creator(%DataTableMessage{} = data_table, nil, variable_cells, value_cells) do
    pickle_data_table_creator2(data_table, nil, variable_cells, value_cells)
  end

  defp pickle_data_table_creator(%DataTableMessage{} = data_table, %DocStringMessage{} = doc_string, variable_cells, value_cells) do
    argument_index = if data_table do
      if data_table.location.line > doc_string.location.line do
        2
      else
        1
      end
    end
    pickle_data_table_creator2(data_table, argument_index, variable_cells, value_cells)
  end

  defp pickle_data_table_creator2(%DataTableMessage{} = data_table, argument_index, variable_cells, value_cells) do
    table_row_messages =
      Enum.reduce(data_table.rows, [], fn %TableRowMessage{} = row, pickle_table_rows_acc ->
        new_cells =
          Enum.reduce(row.cells, [], fn cell, pickle_table_cell_acc ->
            new_table_cell_message = %PickleTableCellMessage{
              value: interpolate(cell.value, variable_cells, value_cells)
            }

            [new_table_cell_message | pickle_table_cell_acc]
          end)
          |> Enum.reverse()

        [%PickleTableRowMessage{cells: new_cells} | pickle_table_rows_acc]
      end)
      |> Enum.reverse()

    %PickleTableMessage{argument_index: argument_index, rows: table_row_messages}
  end

  alias CucumberMessages.PickleDocString, as: PickleDocStringMessage
  alias CucumberMessages.DocString, as: DocStringMessage

  defp pickle_doc_string_creator(%DocStringMessage{} = doc_string, nil, variable_cells, value_cells) do
    pickle_doc_string_creator2(doc_string, nil, variable_cells, value_cells)
  end

  defp pickle_doc_string_creator(%DocStringMessage{} = doc_string, %DataTableMessage{} = data_table, variable_cells, value_cells) do
    argument_index = if data_table do
      if data_table.location.line > doc_string.location.line do
        1
      else
        2
      end
    end
    pickle_doc_string_creator2(doc_string, argument_index, variable_cells, value_cells)
  end

  defp pickle_doc_string_creator2(%DocStringMessage{} = doc_string, argument_index, variable_cells, value_cells) do
    content = interpolate(doc_string.content, variable_cells, value_cells)
    media_type =
      case doc_string.media_type do
        nil -> nil
        media_type -> interpolate(media_type, variable_cells, value_cells)
      end

    %PickleDocStringMessage{argument_index: argument_index, content: content, media_type: media_type}
  end

  ####################################################
  # Extra Helper functions to reduce "If nil" horror #
  ####################################################

  defp add_ast_node_id(%PickleStepMessage{} = m, nil), do: m

  defp add_ast_node_id(%PickleStepMessage{ast_node_ids: ids} = m, %TableRowMessage{} = row),
    do: %{m | ast_node_ids: ids ++ [row.id]}

  defp add_datatable(%PickleStepMessage{} = m, %StepMessage{data_table: nil}, _, _),
    do: m

  defp add_datatable(
         %PickleStepMessage{} = m,
         %StepMessage{data_table: data_table, doc_string: doc_string},
         variable_cells,
         value_cells
       ) do
    result = pickle_data_table_creator(data_table, doc_string, variable_cells, value_cells)
    argument = m.argument || %PickleStepArgumentMessage{}
    %{m | argument: %{argument | data_table: result}}
  end

  defp add_doc_string(%PickleStepMessage{} = m, %StepMessage{doc_string: nil}, _, _),
    do: m

  defp add_doc_string(
         %PickleStepMessage{} = m,
         %StepMessage{doc_string: doc_string, data_table: data_table},
         variable_cells,
         value_cells
       ) do
    result = pickle_doc_string_creator(doc_string, data_table, variable_cells, value_cells)
    argument = m.argument || %PickleStepArgumentMessage{}
    %{m | argument: %{argument | doc_string: result}}
  end

  defp effective_keyword_type("Conjunction", last_keyword_type), do: last_keyword_type || "Unknown"
  defp effective_keyword_type(nil, _last_keyword_type), do: "Unknown"
  defp effective_keyword_type(keyword_type, _last_keyword_type), do: keyword_type

  defp get_id_and_update_compiler_acc(%@me{id_gen: gen} = compiler_acc) do
    {id, updated_generator} = CucumberGherkin.IdGenerator.get_id(gen)
    updated_acc = %{compiler_acc | id_gen: updated_generator}
    {id, updated_acc}
  end
end
