# frozen_string_literal: true

describe Gherkin do
  let(:options) { { include_source: true, include_gherkin_document: true, include_pickles: true } }

  it 'can process feature file paths' do
    messages = Gherkin.from_paths(['../testdata/good/minimal.feature'], options).to_a

    expect(messages.length).to eq(3)
  end

  it 'can process feature file content' do
    data = File.open('../testdata/good/minimal.feature', 'r:UTF-8', &:read)
    messages = Gherkin.from_source('uri', data, options).to_a

    expect(messages.length).to eq(3)
  end

  it 'can set the default dialect for the feature file content' do
    data = File.open('../testdata/good/i18n_no.feature', 'r:UTF-8', &:read)
    messages = Gherkin.from_source('uri', data, options.merge(default_dialect: 'no')).to_a

    expect(messages.length).to eq(3)
  end
end
