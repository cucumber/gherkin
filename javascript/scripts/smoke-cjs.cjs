const assert = require('node:assert/strict')
const { IdGenerator } = require('@cucumber/messages')
const {
  AstBuilder,
  dialects,
  generateMessages,
  GherkinClassicTokenMatcher,
  GherkinInMarkdownTokenMatcher,
  makeSourceEnvelope,
  Parser,
  TokenScanner,
  compile,
  Errors,
} = require('../dist/cjs/src/index.js')

assert.equal(typeof Parser, 'function', 'Parser should be a class')
assert.equal(typeof AstBuilder, 'function', 'AstBuilder should be a class')
assert.equal(typeof GherkinClassicTokenMatcher, 'function')
assert.equal(typeof GherkinInMarkdownTokenMatcher, 'function')
assert.equal(typeof generateMessages, 'function')
assert.equal(typeof makeSourceEnvelope, 'function')
assert.equal(typeof TokenScanner, 'function')
assert.equal(typeof compile, 'function')
assert.equal(dialects.en.name, 'English', 'dialects.en.name should be English')
assert.equal(typeof Errors.AstBuilderException, 'function')

const parser = new Parser(
  new AstBuilder(IdGenerator.incrementing()),
  new GherkinClassicTokenMatcher()
)
const ast = parser.parse('Feature: hello')
assert.equal(ast.feature.name, 'hello')
assert.equal(ast.feature.language, 'en')

const envelopes = generateMessages(
  'Feature: Foo\n  Scenario: Bar\n    Given x\n',
  'foo.feature',
  'text/x.cucumber.gherkin+plain',
  { includePickles: true, newId: IdGenerator.incrementing() }
)
const pickle = envelopes.find((e) => e.pickle).pickle
assert.equal(pickle.steps[0].text, 'x')

console.log('CJS smoke test passed')
