import ITokenMatcher from "../ITokenMatcher";
import {TokenType} from "../Parser";

export default class GherkinFlavor {

    constructor(public name: string, public fileExtension: string, public tokenMatcher: ITokenMatcher<TokenType>) {

    }

    get mediaType(): string {
        return `text/x.cucumber.gherkin+${this.name}`;
    }
}