import io

def source_event(path):
    event = {
        'source': {
            'uri': path,
            'data': io.open(path, 'r', encoding='utf8', newline='').read(),
            'mediaType': _media_type(path)
        }
    }
    return event


def _media_type(path):
    if(path.endswith(".feature")):
        return 'text/x.cucumber.gherkin+plain'
    if(path.endswith(".feature.md")):
        return 'text/x.cucumber.gherkin+markdown'

class SourceEvents:
    def __init__(self, paths):
        self.paths = paths

    def enum(self):
        return map(source_event, self.paths)
