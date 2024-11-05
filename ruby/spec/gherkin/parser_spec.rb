# frozen_string_literal: true

describe Gherkin::Parser do
  describe '#initialize' do
    it 'can be initialized with no arguments' do
      expect { described_class.new }.not_to raise_error
    end
  end
end
