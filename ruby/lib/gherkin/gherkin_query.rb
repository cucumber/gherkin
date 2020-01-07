module Gherkin
  class Query
    def initialize
      @ast_node_locations = {}
    end

    def update(message)
      update_feature(message.gherkin_document.feature) if message.gherkin_document
    end

    def get_location(ast_node_id)
      return @ast_node_locations[ast_node_id] if @ast_node_locations.has_key?(ast_node_id)
      raise AstNodeNotLocatedException, "No location found for #{ast_node_id} }. Known: #{@ast_node_locations.keys}"
    end

    private

    def update_feature(feature)
      store_nodes_location(feature.tags)

      feature.children.each do |child|
        update_rule(child.rule) if child.rule
        update_background(child.background) if child.background
        update_scenario(child.scenario) if child.scenario
      end
    end

    def update_rule(rule)
      rule.children.each do |child|
        update_background(child.background) if child.background
        update_scenario(child.scenario) if child.scenario
      end
    end

    def update_background(background)
      store_nodes_location(background.steps)
    end

    def update_scenario(scenario)
      store_node_location(scenario)
      store_nodes_location(scenario.tags)
      store_nodes_location(scenario.steps)
      scenario.examples.each { |example| store_nodes_location(example.tags) }
    end

    def store_nodes_location(nodes)
      nodes.each { |node| store_node_location(node) }
    end

    def store_node_location(node)
      @ast_node_locations[node.id] = node.location
    end
  end
end
