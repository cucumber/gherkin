import ITokenMatcher from "../ITokenMatcher";
import {TokenType} from "../Parser";
import GherkinFlavor from "./GherkinFlavor";

/**
 * This class provides a way to extend the gherkin language by adding flavor implementations such as
 * AsciiDoc flavor or Markdown flavor.
 *
 */
export default class CustomFlavorRegistry {
    private flavors: Array<GherkinFlavor>;

    constructor() {
        this.flavors = new Array<GherkinFlavor>();
    }

    public registerFlavor(name: string, fileExtension: string, tokenMatcher: ITokenMatcher<TokenType>) {
        this.flavors.push(new GherkinFlavor(name, fileExtension, tokenMatcher));
    }

    mediaTypeFor(uri: string): string {
        const flavor = this.flavors.find(flavor => uri.endsWith(flavor.fileExtension))
        return flavor.mediaType;
    }

    tokenMatcherFor(sourceMediaType: string): ITokenMatcher<TokenType> {
        const flavor = this.flavors.find(flavor => flavor.mediaType === sourceMediaType);
        return flavor.tokenMatcher;
    }

    private static instance: CustomFlavorRegistry;
    public static getInstance() {
       if(!this.instance) {
           this.instance = new CustomFlavorRegistry();
       }

       return this.instance;
    }
}