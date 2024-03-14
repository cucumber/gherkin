defmodule CucumberGherkin.MixProject do
  use Mix.Project

  @github "https://github.com/cucumber/gherkin/tree/main/elixir"

  def project do
    [
      app: :cucumber_gherkin,
      version: "28.0.0",
      name: "CucumberGherkin",
      description: description(),
      package: package(),
      elixir: "~> 1.10",
      start_permanent: Mix.env() == :prod,
      deps: deps()
    ]
  end

  # Run "mix help compile.app" to learn about applications.
  def application do
    [
      extra_applications: [:logger]
    ]
  end

  # Run "mix help deps" to learn about dependencies.
  defp deps do
    [
      {:elixir_uuid, "~> 1.2"},
      {:cucumber_messages, "~> 15.0"},
      {:ex_doc, "~> 0.31", only: :dev, runtime: false}
    ]
  end

  defp description() do
    "Elixir Gherkin parser."
  end

  defp package() do
    [
      licenses: ["MIT"],
      source_url: @github,
      links: %{"GitHub" => @github}
    ]
  end
end
