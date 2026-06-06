#!/usr/bin/env node
import { readFileSync, writeFileSync } from 'node:fs'
import { dirname, join } from 'node:path'
import { fileURLToPath } from 'node:url'

const here = dirname(fileURLToPath(import.meta.url))
const srcDir = join(here, '..', 'src')
const json = readFileSync(join(srcDir, 'gherkin-languages.json'), 'utf-8')

const ts = `// Generated from gherkin-languages.json. Do not edit.
import type Dialect from './Dialect.js'

const dialects: Readonly<{ [key: string]: Dialect }> = ${json.trimEnd()}

export default dialects
`

writeFileSync(join(srcDir, 'gherkin-languages.ts'), ts)
