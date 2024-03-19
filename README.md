# Minishell

## Introduction
Welcome to Minishell, a simple Unix shell implementation written in C. Minishell provides a command-line interface for users to interact with the operating system, executing commands and managing processes.
42 project, recoding our own little bash. A program capable of parsing a prompt and launching executables with arguments, along with a few built-in functions.

## Final grade : 101/125

## Features
- **Command Execution**: Minishell can execute external commands and display their output to the user.
- **Input/Output Redirection**: Users can redirect command input and output using the `<`, `>`, and `>>` operators.
- **Heredoc**: Minishell supports heredoc, allowing users to specify a delimiter and input text until that delimiter is encountered.
- **Piping**: Minishell supports command piping, allowing users to chain multiple commands together using the `|` operator.
- **Basic Environment Variables**: Users can set and access basic environment variables within Minishell.
- **Signal Handling**: Minishell handles signals such as SIGINT (Ctrl+C) and SIGQUIT (Ctrl+\) to ensure proper termination of processes.

## Getting Started
To run Minishell on your local machine, follow these steps:

1. Clone this repository to your local machine:
   ```bash
   git clone git@github.com:oumaima-aarabe/Minishell.git

2. Using ``make`` will create the ``minishell`` executable.

3. Simply run it with :

```
./minishell
```

### Available options

Minishell runs executables from an absolute, relative or environment PATH (``/bin/ls`` or ``ls``), including arguments or options. ``'`` and ``"`` work the same as bash, except for multiline commands.

You can use redirections ``>`` ``>>`` ``<`` and pipes ``|``.

as well as `<<` operator .

Environment variables are handled, like ``$HOME``, including the return code ``$?``.

Finally, you can use ``Ctrl-C`` to interrupt and ``Ctrl-\`` to quit a program, as well as ``Ctrl-D`` to throw an EOF, same as in bash.

A few of the functions are "built-in", meaning we don't call the executable, we re-coded them directly:

- `echo` with option `-n`
- `cd` with only a relative or absolute path
- `pwd` with no options
- `export` with no options
- `unset` with no options
- `env` with no options or arguments
- `exit` with no options
