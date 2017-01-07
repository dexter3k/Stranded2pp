# Lexical structure

## Notice

This document is incomplete

## Identifiers

Identifiers start with any alphabetic character or underscore (`_`) symbol
followed by any number of alphanumeric characters and/or underscores.
Identifiers are case-sensitive.

Examples:

```
_fOo123
foo
Foo
_122Foo__333
123foo // illegal, must begin with alphabetic (a-z, A-Z) or _, not number (0-9)
```

## Keywords

Some keywords cannot be used as identifiers:
  * `on`
  * `if`
  * `elseif`
  * `else`
  * `skip`
  * `loop`

## Operators

| Operator | Description |
|:--------:|:-----------:|
| `@` | Error oppression |
| `$` | Variable access |
| `=` | Assign |
| `+` | Addition |
| `-` | Subtraction/Negation |
| `++` | Increment |
| `--` | Decrement |
| `+=` | Addition assignment |
| `-=` | Subtraction assignment |
| `*` | Multiplication |
| `/` | Division |
| `*=` | Multiplication assignment |
| `/=` | Division assignment |
| `==` | Equal to |
| `>` | Greater than |
| `<` | Less than |
| `>=` | Greater than or equal to |
| `<=` | Less than or equal to |

## Other tokens

  * `{`
  * `}`
  * `:`
  * `"`
  * `'`
  * `;`
  * `(`
  * `)`
  * `,`
