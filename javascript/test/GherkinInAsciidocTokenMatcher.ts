import {GherkinInMarkdownTokenMatcher} from "../src";

export default class GherkinInAsciidocTokenMatcher extends GherkinInMarkdownTokenMatcher {
    constructor(defaultDialectName: string = 'en') {
        const asciidocPrefixes = {
            BULLET: '^(\\s*[*\\.-]\\s*)',
            HEADER: '^(={1,6}\\s)',
        }
        super(defaultDialectName, asciidocPrefixes);
    }

}