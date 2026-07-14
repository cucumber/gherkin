defmodule CucumberGherkin.UnexpectedEOFError do
  @moduledoc false
  defstruct [:line, :expected_tokens, :comment]

  defimpl CucumberGherkin.ParserException do
    def get_message(%{} = me) do
      expected_string = Enum.join(me.expected_tokens, ", ")
      base = "(#{me.line.index}:0): "
      base <> "unexpected end of file, expected: #{expected_string}"
    end

    def generate_message(%{} = error), do: %{error | message: get_message(error)}

    def get_location(%{} = me), do: %CucumberMessages.Location{line: me.line.index}
  end
end
