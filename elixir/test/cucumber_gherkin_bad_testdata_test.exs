defmodule CucumberGherkinBadTestdataTest do
  use ExUnit.Case
  require Logger

  @moduletag timeout: :infinity

  @files [
    "../testdata/bad/backslash_at_end_of_line_in_datatable.feature",
    # Doesn't fail.
    # "../testdata/bad/file_ends_with_open_docstring.feature",
    "../testdata/bad/inconsistent_cell_count.feature",
    "../testdata/bad/invalid_language.feature",
    "../testdata/bad/multiple_parser_errors.feature",
    "../testdata/bad/not_gherkin.feature",
    "../testdata/bad/repeated_step_docstring.feature",
    "../testdata/bad/single_parser_error.feature",
    # Off by one
    # "../testdata/bad/unexpected_end_of_file.feature",
    "../testdata/bad/unexpected_eof.feature",
    "../testdata/bad/unfinished_datatable.feature",
    "../testdata/bad/whitespace_in_tags.feature"
  ]

  @tag :bad
  test "BAD: compare all bad testdata" do
    opts = [:no_source, :no_pickles, :predictable_ids]

    results =
      Enum.map(@files, fn path ->
        correct_output = File.read!(path <> ".errors.ndjson")
        result = CucumberGherkin.parse_path(path, opts) |> CucumberGherkin.print_messages(:ndjson)

        {path, correct_output == result, result, correct_output}
      end)

    total_result_boolean = Enum.all?(results, fn {_path, result, _actual, _expected} -> result end)

    results |> construct_info_message("BAD TESTDATA") |> report_to_logger(total_result_boolean)

    assert total_result_boolean
  end

  defp construct_info_message(results, report_label) do
    start_line = "#### #{report_label} ####"
    content = Enum.map(results, &construct_info_line/1) |> List.flatten() |> Enum.join("\n")
    end_line = String.duplicate("#", 20)
    Enum.join([start_line, content, end_line], "\n")
  end

  defp construct_info_line({path, false, actual, expected}), do: "# ERROR => #{path}\nExpected:\n#{expected}\nActual:\n#{actual}"
  defp construct_info_line({path, true, _actual, _expected}), do: "# OK    => #{path}"

  defp report_to_logger(message, true), do: Logger.debug("\n" <> message)
  defp report_to_logger(message, false), do: Logger.error("\n" <> message)
end
