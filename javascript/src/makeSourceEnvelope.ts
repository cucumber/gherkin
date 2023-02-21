import * as messages from '@cucumber/messages'
import CustomFlavorRegistry from "./flavors/CustomFlavorRegistry";

export default function makeSourceEnvelope(data: string, uri: string): messages.Envelope {
  let mediaType: string
  let customFlavorsRegistry = CustomFlavorRegistry.getInstance();

  if (uri.endsWith('.feature')) {
    mediaType = 'text/x.cucumber.gherkin+plain'
  } else if (uri.endsWith('.md')) {
    mediaType = 'text/x.cucumber.gherkin+markdown'
  } else {
    mediaType = customFlavorsRegistry.mediaTypeFor(uri);
  }
  if (!mediaType) throw new Error(`The uri (${uri}) must end with .feature or .md`)
  return {
    source: {
      data,
      uri,
      mediaType,
    },
  }
}
