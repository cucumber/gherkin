# frozen_string_literal: true

describe Gherkin::Pickles::Compiler do
  describe 'interpolation' do
    def step_texts(value)
      feature = <<~FEATURE
        Feature: Interpolation

          Scenario Outline: Substitution
            Given <value>

            Examples:
              | value |
              | #{value} |
      FEATURE

      Gherkin
        .from_source('uri', feature, include_pickles: true)
        .filter_map(&:pickle)
        .flat_map { |pickle| pickle.steps.map(&:text) }
    end

    it 'substitutes a value' do
      expect(step_texts('foo')).to eq(['foo'])
    end

    it 'substitutes a value with a backslash' do
      expect(step_texts('a\\\\b')).to eq(['a\b'])
    end

    it 'substitutes a value with a backtick after a backslash' do
      expect(step_texts('a\`b')).to eq(['a\`b'])
    end

    it 'substitutes a value with an ampersand after a backslash' do
      expect(step_texts('a\&b')).to eq(['a\&b'])
    end
  end
end
