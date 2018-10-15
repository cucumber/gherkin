/* eslint-env mocha */
const assert = require('assert')
const cm = require('cucumber-messages').io.cucumber.messages
const { fromPaths, fromSources } = require('../src/index')

describe('gherkin (JavaScript)', () => {
  it('parses gherkin from the file system', async () => {
    const messages = await streamToArray(
      fromPaths(['testdata/good/minimal.feature'])
    )
    assert.strictEqual(messages.length, 3)
  })

  it('parses gherkin from STDIN', async () => {
    const source = cm.Source.fromObject({
      uri: 'test.feature',
      data: `Feature: Minimal

  Scenario: minimalistic
    Given the minimalism
`,
      media: cm.Media.fromObject({
        encoding: 'UTF-8',
        contentType: 'text/x.cucumber.gherkin+plain',
      }),
    })

    const messages = await streamToArray(fromSources([source]))
    assert.strictEqual(messages.length, 3)
  })
})

function streamToArray(readableStream) {
  return new Promise((resolve, reject) => {
    const items = []
    readableStream.on('data', items.push.bind(items))
    readableStream.on('error', reject)
    readableStream.on('end', () => resolve(items))
  })
}
