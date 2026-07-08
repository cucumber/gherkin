defmodule CucumberGherkinGoodTestdataTest do
  use ExUnit.Case
  require Logger

  @moduletag timeout: :infinity

  @files [
    "../testdata/good/minimal.feature",
    "../testdata/good/background.feature",
    "../testdata/good/complex_background.feature",
    "../testdata/good/conjunctions.feature",
    "../testdata/good/datatables.feature",
    "../testdata/good/datatables_with_new_lines.feature",
    "../testdata/good/descriptions.crlf.feature",
    "../testdata/good/descriptions.feature",
    "../testdata/good/descriptions_with_comments.feature",
    "../testdata/good/docstrings.crlf.feature",
    "../testdata/good/docstrings.feature",
    # Missing data field
    # "../testdata/good/empty.feature",
    "../testdata/good/escaped_pipes.feature",
    "../testdata/good/example_token_multiple.feature",
    "../testdata/good/example_tokens_everywhere.feature",
    # Not implemented
    # "../testdata/good/extra_table_content.feature",
    "../testdata/good/i18n_emoji.feature",
    "../testdata/good/i18n_fr.feature",
    "../testdata/good/i18n_no.feature",
    "../testdata/good/incomplete_background_1.feature",
    "../testdata/good/incomplete_background_2.feature",
    "../testdata/good/incomplete_feature_1.feature",
    "../testdata/good/incomplete_feature_2.feature",
    "../testdata/good/incomplete_feature_3.feature",
    "../testdata/good/incomplete_scenario.feature",
    "../testdata/good/incomplete_scenario_outline.feature",
    "../testdata/good/language.feature",
    "../testdata/good/minimal-example.feature",
    "../testdata/good/minimal.crlf.feature",
    "../testdata/good/minimal.feature",
    "../testdata/good/padded_example.feature",
    # not implemented
    # "../testdata/good/prefixed-keywords.feature",
    "../testdata/good/readme_example.feature",
    "../testdata/good/rule.feature",
    "../testdata/good/rule_with_tag.feature",
    "../testdata/good/rule_without_name_and_description.feature",
    "../testdata/good/scenario_outline.feature",
    "../testdata/good/scenario_outline_no_newline.feature",
    "../testdata/good/scenario_outline_with_docstring.feature",
    "../testdata/good/scenario_outline_with_value_with_dollar_sign.feature",
    "../testdata/good/scenario_outline_with_value_with_trailing_backslash.feature",
    "../testdata/good/scenario_outlines_with_tags.feature",
    "../testdata/good/several_examples.feature",
    "../testdata/good/spaces_in_language.feature",
    "../testdata/good/star-keywords.feature",
    "../testdata/good/step_with_datatable_and_docstring.feature",
    "../testdata/good/tagged_feature_with_scenario_outline.feature",
    "../testdata/good/tags.feature",
    # not implemented
    # "../testdata/good/trim_space.feature",
    # "../testdata/good/trim_tab.feature",
    "../testdata/good/very_long.feature"
  ]

  @tag :good
  @tag :tokens
  test "TOKENS: compare all testdata" do
    results =
      Enum.map(@files, fn path ->
        correct_output = File.read!(path <> ".tokens")
        tokenized_output = CucumberGherkin.tokenize(path)
        {path, correct_output == tokenized_output, tokenized_output, correct_output}
      end)

    total_result_boolean = Enum.all?(results, fn {_path, result, _actual, _expected} -> result end)

    results
    |> construct_info_message("TOKENS TESTDATA (GOOD)")
    |> report_to_logger(total_result_boolean)

    assert total_result_boolean
  end

  @tag :good
  @tag :source
  test "SOURCE: compare all testdata" do
    opts = [:no_pickles, :predictable_ids, :no_ast]

    results = test_files_that_end_with(".source.ndjson", opts)
    total_result_boolean = Enum.all?(results, fn {_path, result, _actual, _expected} -> result end)

    results
    |> construct_info_message("SOURCE TESTDATA (GOOD)")
    |> report_to_logger(total_result_boolean)

    assert total_result_boolean
  end

  @tag :good
  @tag :ast
  test "AST: compare all testdata" do
    opts = [:no_pickles, :predictable_ids, :no_source]

    results = test_files_that_end_with(".ast.ndjson", opts)
    total_result_boolean = Enum.all?(results, fn {_path, result, _actual, _expected} -> result end)
    results
    |> construct_info_message("AST TESTDATA (GOOD)")
    |> report_to_logger(total_result_boolean)

    assert total_result_boolean
  end

  @tag :good
  @tag :pickles
  test "PICKLES: compare all testdata" do
    opts = [:no_ast, :predictable_ids, :no_source]
    results = test_files_that_end_with(".pickles.ndjson", opts)
    total_result_boolean = Enum.all?(results, fn {_path, result, _actual, _expected} -> result end)

    results
    |> construct_info_message("PICKLES TESTDATA (GOOD)")
    |> report_to_logger(total_result_boolean)

    assert total_result_boolean
  end

  defp test_files_that_end_with(extension, opts) do
    Enum.map(@files, fn path ->
      correct_output = File.read!(path <> extension)
      result = CucumberGherkin.parse_path(path, opts) |> CucumberGherkin.print_messages(:ndjson)
      {path, correct_output == result, result, correct_output }
    end)
  end

  defp construct_info_message(results, report_label) do
    start_line = "#### #{report_label} ####"
    content = Enum.map(results, &construct_info_line/1) |> List.flatten() |> Enum.join("\n")
    end_line = String.duplicate("#", 20)
    Enum.join([start_line, content, end_line], "\n")
  end

  defp construct_info_line({path, false, actual, expected}), do: "# ERROR => #{path}" <> "\nExpected:\n#{expected}\nActual:\n#{actual}"
  defp construct_info_line({path, true, _actual, _expected}), do: "# OK    => #{path}"

  defp report_to_logger(message, true), do: Logger.debug("\n" <> message)
  defp report_to_logger(message, false), do: Logger.error("\n" <> message)
end
