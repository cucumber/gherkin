defmodule CucumberGherkin.AstStep do
  @moduledoc false

  defstruct data_table: nil,
            doc_string: nil,
            id: "",
            keyword: "",
            keyword_type: "Unknown",
            location: nil,
            text: ""
end
