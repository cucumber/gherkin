# frozen_string_literal: true

module Gherkin
  module Stream
    describe ParserMessageStream do
      let(:feature_content) do
        "Feature: my feature\n" \
          "  Scenario: a scenario\n" \
          "    Given some context"
      end

      let(:source_feature) do
        Cucumber::Messages::Source.new(
          uri: '//whatever/uri',
          data: feature_content,
          media_type: 'text/x.cucumber.gherkin+plain'
        )
      end

      let(:options) do
        {
          include_gherkin_document: true
        }
      end

      let(:gherkin_document) do
        ParserMessageStream.new([], [source_feature], options).messages.first.gherkin_document
      end

      let(:scenario_id) { gherkin_document.feature.children.first.scenario.id }

      context '#messages' do
        it "raises an exception on second iteration" do
          messages = ParserMessageStream.new([], [source_feature], options).messages

          expect { messages.map(&:to_s) }.not_to raise_exception
          expect { messages.map(&:to_s) }.to raise_exception(Gherkin::DoubleIterationException)
        end
      end

      context 'options.id_generator' do
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
  end
end
