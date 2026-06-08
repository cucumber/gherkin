defmodule CucumberGherkin.PickleStep do
  @moduledoc false

  defstruct argument: nil,
            ast_node_ids: [],
            id: "",
            text: "",
            type: "Unknown"
end
