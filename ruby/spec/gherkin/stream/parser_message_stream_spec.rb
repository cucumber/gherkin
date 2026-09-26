# frozen_string_literal: true

describe Gherkin::Stream::ParserMessageStream do
  subject(:gherkin_document) { messages.first.gherkin_document }

  let(:messages) { described_class.new(sources: [source_feature], options: options).messages }
  let(:source_feature) do
    Cucumber::Messages::Source.new(
      uri: '//whatever/uri',
      data: feature_content,
      media_type: 'text/x.cucumber.gherkin+plain'
    )
  end
  let(:feature_content) do
    <<~CONTENT
      Feature: my feature
        Scenario: a scenario
        Given some context
    CONTENT
  end
  let(:options) { { include_gherkin_document: true } }
  let(:scenario_id) { gherkin_document.feature.children.first.scenario.id }

  describe '#messages' do
    it "raises an exception on the second iteration" do
      expect { messages.map(&:to_s) }.not_to raise_exception
      expect { messages.map(&:to_s) }.to raise_exception(Gherkin::DoubleIterationException)
    end
  end

  describe 'Markdown with Gherkin' do
    let(:options) { { include_source: false, include_gherkin_document: true, include_pickles: false } }

    context 'when selected by a .feature.md URI' do
      let(:source_feature) do
        Cucumber::Messages::Source.new(
          uri: 'markdown.feature.md',
          data: feature_content,
          media_type: 'text/x.cucumber.gherkin+plain'
        )
      end
      let(:feature_content) do
        <<~CONTENT
          # Feature: Markdown feature
          ## Scenario: Markdown scenario
          - Given a Markdown step
        CONTENT
      end

      let(:markdown_parse_result) do
        feature = gherkin_document.feature
        scenario = feature.children.first.scenario
        step = scenario.steps.first

        {
          feature_name: feature.name,
          feature_location: feature.location.to_h,
          scenario_location: scenario.location.to_h,
          step_text: step.text,
          step_location: step.location.to_h
        }
      end
      let(:expected_markdown_parse_result) do
        {
          feature_name: 'Markdown feature',
          feature_location: { line: 1, column: 3 },
          scenario_location: { line: 2, column: 4 },
          step_text: 'a Markdown step',
          step_location: { line: 3, column: 3 }
        }
      end

      it 'parses Markdown headings and bullet steps with source locations' do
        expect(markdown_parse_result).to eq(expected_markdown_parse_result)
      end
    end

    context 'when the MDG table has inconsistent cells' do
      let(:source_feature) do
        Cucumber::Messages::Source.new(
          uri: 'malformed.feature.md',
          data: feature_content,
          media_type: 'text/x.cucumber.gherkin+markdown'
        )
      end
      let(:feature_content) do
        <<~CONTENT
          # Feature: malformed table
          ## Scenario: inconsistent rows
          * Given a table
            | key | value |
            | only |
        CONTENT
      end

      it 'reports the original source line and column' do
        parse_error = messages.first.parse_error

        expect(
          uri: parse_error.source.uri,
          location: parse_error.source.location.to_h,
          message: parse_error.message
        ).to eq(
          uri: 'malformed.feature.md',
          location: { line: 5, column: 3 },
          message: '(5:3): inconsistent cell count within the table'
        )
      end
    end
  end

  describe '#options.id_generator' do
    context 'when not set' do
      it 'generates random UUIDs' do
        expect(scenario_id).to match(/[0-9a-fA-F]{8}\-[0-9a-fA-F]{4}\-[0-9a-fA-F]{4}\-[0-9a-fA-F]{4}\-[0-9a-fA-F]{12}/)
      end
    end

    context 'when set' do
      let(:id_generator) { double }
      let(:options) do
        {
          include_gherkin_document: true,
          id_generator: id_generator
        }
      end

      it 'uses the generator instance to produce the IDs' do
        allow(id_generator).to receive(:new_id).and_return('some-random-id')

        expect(scenario_id).to eq('some-random-id')
      end
    end
  end
end
