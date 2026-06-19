defmodule CucumberGherkin.Pickle do
  @moduledoc false

  defstruct ast_node_ids: [],
            id: "",
            language: "",
            location: nil,
            name: "",
            steps: [],
            tags: [],
            uri: ""
end
