import type { Comment, IdGenerator, Location, TableCell, TableRow, Tag } from '@cucumber/messages'
import type IToken from './IToken.js'

export interface IAstBuilder<AstNode, TokenType, RuleType> {
  stack: AstNode[]
  comments: Comment[]
  newId: IdGenerator.NewId

  reset(): void

  startRule(ruleType: RuleType): void

  endRule(): void

  build(token: IToken<TokenType>): void

  // biome-ignore lint/suspicious/noExplicitAny: result type varies per builder implementation
  getResult(): any

  // biome-ignore lint/suspicious/noExplicitAny: node representation varies per builder implementation
  currentNode(): any

  getLocation(token: IToken<TokenType>, column?: number): Location

  getTags(node: AstNode): readonly Tag[]

  getCells(tableRowToken: IToken<TokenType>): readonly TableCell[]

  // biome-ignore lint/suspicious/noExplicitAny: description type varies per builder implementation
  getDescription(node: AstNode): any

  // biome-ignore lint/suspicious/noExplicitAny: step representation varies per builder implementation
  getSteps(node: AstNode): any[]

  getTableRows(node: AstNode): readonly TableRow[] | undefined

  ensureCellCount(rows: readonly TableRow[]): void

  // biome-ignore lint/suspicious/noExplicitAny: transformed node varies per rule type
  transformNode(node: AstNode): any
}
