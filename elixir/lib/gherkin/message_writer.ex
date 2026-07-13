defmodule CucumberGherkin.MessageWriter do
  @moduledoc false

  def convert_envelopes_to(envelopes, :ndjson) do
    envelopes
    |> Enum.map(&Jason.encode!/1)
    |> Enum.join("\n")
    |> case do
      "" -> ""
      result -> result <> "\n"
    end
  end
end
