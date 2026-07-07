import { type Envelope, SourceMediaType } from '@cucumber/messages'

export default function makeSourceEnvelope(data: string, uri: string): Envelope {
  let mediaType: SourceMediaType
  if (uri.endsWith('.feature')) {
    mediaType = SourceMediaType.TEXT_X_CUCUMBER_GHERKIN_PLAIN
  } else if (uri.endsWith('.md')) {
    mediaType = SourceMediaType.TEXT_X_CUCUMBER_GHERKIN_MARKDOWN
  }
  if (!mediaType) {
    throw new Error(`The uri (${uri}) must end with .feature or .md`)
  }
  return {
    source: {
      data,
      uri,
      mediaType,
    },
  }
}
