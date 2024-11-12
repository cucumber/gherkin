# frozen_string_literal: true

module Gherkin
  class Query
    def initialize
      @ast_node_locations = {}
      @scenario_parent_locations = {}
      @background_locations = {}
    end

    def update(message)
      update_feature(message.gherkin_document.feature) if message.gherkin_document
    end

    def scenario_parent_locations(scenario_node_id)
      return @scenario_parent_locations[scenario_node_id] if @scenario_parent_locations.has_key?(scenario_node_id)

      raise AstNodeNotLocatedException, "No scenario parent locations found for #{scenario_node_id} }. Known: #{@scenario_parent_locations.keys}"
    end

    def location(ast_node_id)
      return @ast_node_locations[ast_node_id] if @ast_node_locations.has_key?(ast_node_id)

      raise AstNodeNotLocatedException, "No location found for #{ast_node_id} }. Known: #{@ast_node_locations.keys}"
    end

    private

    def update_feature(feature)
      return if feature.nil?

      store_nodes_location(feature.tags)

      feature.children.each do |child|
        update_rule(feature, child.rule) if child.rule
        update_background(feature, child.background) if child.background
        update_scenario(feature, child.rule, child.scenario) if child.scenario
      end
    end

    def update_rule(feature, rule)
      return if rule.nil?

      store_nodes_location(rule.tags)
      rule.children.each do |child|
        update_background(rule, child.background) if child.background
        update_scenario(feature, rule, child.scenario) if child.scenario
      end
    end

    def update_background(parent, background)
      update_steps(background.steps)
      @background_locations[parent] = background.location
    end

    def update_scenario(feature, rule, scenario)
      store_node_location(scenario)
      store_nodes_location(scenario.tags)
      update_steps(scenario.steps)
      scenario.examples.each do |examples|
        store_nodes_location(examples.tags || [])
        store_nodes_location(examples.table_body || [])
      end

      @scenario_parent_locations[scenario.id] = [
        feature.location,
        @background_locations[feature],
        rule&.location,
        @background_locations[rule],
      ].compact
    end

    def update_steps(steps)
      store_nodes_location(steps)
    end

    def store_nodes_location(nodes)
      nodes.each { |node| store_node_location(node) }
    end

    def store_node_location(node)
      @ast_node_locations[node.id] = node.location
    end
  end
end
