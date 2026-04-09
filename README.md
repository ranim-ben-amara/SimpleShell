# SimpleShell

A minimalist shell implementation in C that parses and processes command-line input. This project demonstrates core shell functionality including command tokenization, parsing, logical operators, and parallel execution support.

## Features

- **Command Tokenization**: Breaks user input into tokens separated by whitespace
- **Simple Commands**: Parses program names and their arguments
- **Compound Commands**: Handles logical operators (`&&` for AND, `||` for OR)
- **Command Sequences**: Supports chaining multiple commands with operator precedence
- **Parallel Execution**: Executes commands in parallel using the `&` operator

## Project Structure

```text
├── main.c          # Entry point and main shell loop
├── parse.c         # Command parsing implementation
├── parse.h         # Data structure definitions and function declarations
├── Makefile        # Build configuration
└── README.md       # This file
```

## Building

To compile the project, run:

```bash
make
```

This will generate a `shell` executable in the current directory.

To clean up compiled objects:

```bash
make clean
```

## Usage

Run the shell:

```bash
./shell
```

The shell will prompt you to enter a command:

```text
Enter a command: ls -la
```

### Supported Command Syntax

- **Simple command**: `program arg1 arg2 ...`
- **Logical AND**: `command1 && command2` (command2 runs if command1 succeeds)
- **Logical OR**: `command1 || command2` (command2 runs if command1 fails)
- **Parallel execution**: `command &` (runs command in background)
- **Command sequences**: `command1; command2; command3`
- **Complex combinations**: `cmd1 && cmd2; cmd3 || cmd4 &`

## Data Structures

### SimpleCommand

```c
struct SimpleCommand {
    char program_name[MAX_TOKEN_LEN];
    char args[MAX_NB_ARGS][MAX_TOKEN_LEN];
    int nb_args;
};
```

### CompoundCommand

```c
struct CompoundCommand {
    SimpleCommand cmd1;
    SimpleCommand cmd2;
    CommandOperator op;  // OPERATOR_AND or OPERATOR_OR
};
```

### CommandSequence

```c
struct CommandSequence {
    CompoundCommand cmds[MAX_NB_CMDS];
    int nb_cmds;
    bool in_parallel;
};
```

## Limitations

- Maximum of 1000 tokens per input
- Maximum token length: 50 characters
- Maximum of 10 arguments per command
- Maximum of 10 commands per sequence
- Uses deprecated `gets()` function (security concern - consider using `fgets()`)

## Future Enhancements

- Implement command execution (currently only parses)
- Add pipe (`|`) operator support
- Add input/output redirection (`<`, `>`, `>>`)
- Improve input validation and error handling
- Replace `gets()` with safer alternatives like `fgets()`
- Implement proper interactive shell loop
