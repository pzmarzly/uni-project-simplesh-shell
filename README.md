# simplesh - shell written in under 1KLOC of C

Features:

- setting environmental variables via `export`,
- redirecting to and from files,
- multi-word arguments via quoting or `\ `,
- GNU readline input and history,
- colors,
- using `$PATH` to search for executables,
- `cd` with no arguments jumps to home directory,
- no dependencies except for GNU readline.

Caveats:

- quoted strings are not concatenated, that is `"a""b"` will be interpreted as `"a\"\"b"`
