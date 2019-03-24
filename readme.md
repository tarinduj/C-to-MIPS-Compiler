[![Build Status](https://travis-ci.com/adamurban98/langproc-2018-cw-4b825dc642cb6eb9a060e54bf8d69288fbee4904.svg?token=qLnpjKRfRdRW4ZVxWv9Q&branch=master)](https://travis-ci.com/adamurban98/langproc-2018-cw-4b825dc642cb6eb9a060e54bf8d69288fbee4904)

C89 to MIPS compiler
==============================

Usage
------------------------------
- build compiler `make bin/c_compiler`
- build and run Catch2 unit testing `make test` or `make bin/test && bin/test [accepts catch2 options]`
- run test cases and output csv `./test ref|our`
- run test cases and output in a table format `.\test_column ref|our`
- option `ref` uses the _reference_ gcc compiler
- optin `our` uses our compiler

### Using our compiler
```
usage:
  c_compiler <input> options

where options are:
  -?, -h, --help       display usage information
  -c, -S, --compile    compile from C98 to MIPS
  -t, --translate      translate from C89 to Python
  -o <output>          place the output into <file>

```

### Explanation of logs
```
[MSG] Important messages, even for the user.
[CON] Messages from the the context manager, mostly internal.
[LOG] Internal logs.
[ERR] Error messages.
```

External libraries
---------------------
- Unit testing [Catch2](https://github.com/catchorg/Catch2)
- Command line options parsing [Clara](https://github.com/catchorg/Clara)
- Console coloring [rang](https://github.com/agauniyal/rang)
- String formatting [{fmt}](https://github.com/fmtlib/fmt)

Footnotes
--------------------
This is a C89 to MIPS / Python compiler which. It was written as the coursework to the second year EIE module Language Processors at the department of [EEE Imperial College London](https://www.imperial.ac.uk/electrical-engineering) 