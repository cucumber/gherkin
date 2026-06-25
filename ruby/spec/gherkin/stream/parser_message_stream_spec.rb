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
