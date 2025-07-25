# mock

## Current Goal: Implement SQL Lexer

Building a lexer to tokenize SQL commands before parsing into an AST.

### Lexer Requirements

**Core Responsibilities:**
1. **Token Recognition** - Identify and categorize:
   - Keywords: `SELECT`, `FROM`, `WHERE`, `INSERT`, `UPDATE`, `DELETE`, `INTO`, `VALUES`
   - Identifiers: table names, column names (`users`, `name`, `id`)
   - String literals: `'hello world'`, `"john doe"`
   - Numbers: `42`, `3.14`, `0`, `-5`
   - Operators: `=`, `!=`, `<>`, `<`, `>`, `<=`, `>=`
   - Punctuation: `(`, `)`, `,`, `;`, `*`

2. **Character Processing:**
   - Read input character by character
   - Skip whitespace (spaces, tabs, newlines)
   - Handle escape sequences in strings (`\'`, `\"`, `\\`)
   - Recognize multi-character tokens (`!=`, `<=`)

3. **Output Generation:**
   - Create token objects with type + value
   - Return array/list of tokens
   - Mark end of input

4. **Error Detection:**
   - Unterminated strings
   - Invalid characters
   - Malformed numbers

5. **Position Tracking:**
   - Line and column numbers for error reporting
   - Character offset

**Target Function:**
```c
Token* tokenize(const char* sql_command, int* token_count);
```

**Example Transformation:**
Input: `"SELECT name FROM users;"`
Output: `[SELECT] [IDENTIFIER:name] [FROM] [IDENTIFIER:users] [SEMICOLON]`

## Links
- https://cstack.github.io/db_tutorial/
