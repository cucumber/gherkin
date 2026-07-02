import type { Location, StepKeywordType } from '@cucumber/messages'

export interface IGherkinLine {
  readonly lineNumber: number
  readonly isEmpty: boolean
  readonly indent?: number
  readonly trimmedLineText: string

  getTableCells(): readonly Item[]

  startsWith(prefix: string): boolean

  getRestTrimmed(length: number): string

  getLineText(number: number): string

  startsWithTitleKeyword(keyword: string): boolean
}

// Represents tags or table cells
export type Item = {
  column: number
  text: string
}

export default interface IToken<TokenType> {
  location: Location
  line: IGherkinLine

  isEof: boolean
  matchedText?: string
  matchedType: TokenType
  matchedItems: readonly Item[]
  matchedKeyword: string
  matchedKeywordType: StepKeywordType
  matchedIndent: number
  matchedGherkinDialect: string
  getTokenValue(): string
}
