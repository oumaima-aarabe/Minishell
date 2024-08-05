# Minishell

## Introduction

Welcome to Minishell, a simple Unix shell implementation written in C. Minishell provides a command-line interface for users to interact with the operating system, executing commands and managing processes. This project is part of the 42 curriculum, where we recoded our own bash-like shell. It is capable of parsing prompts, launching executables with arguments, and supporting a few built-in functions.

## Final Grade

101/125

## Features

- **Command Execution**: Execute external commands and display their output.
- **Input/Output Redirection**: Redirect command input and output using the `<`, `>`, and `>>` operators.
- **Heredoc**: Specify a delimiter and input text until the delimiter is encountered.
- **Piping**: Chain multiple commands together using the `|` operator.
- **Basic Environment Variables**: Set and access basic environment variables.
- **Signal Handling**: Handle signals such as SIGINT (Ctrl+C) and SIGQUIT (Ctrl+\) for proper process termination.

## Getting Started

### Requirements

To build and run Minishell on macOS, you need the following dependency:

- **GNU Readline**: Provides the library for command-line editing.

### Installing Dependencies on macOS

For macOS, you can use Homebrew to install the necessary packages:

1. **Install Homebrew** (if not already installed):
    ```bash
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    ```

2. **Install Readline**:
    ```bash
    brew install readline
    ```

### Setting Up the Project

Ensure you have the required dependencies installed before building and running Minishell.

To set up and run Minishell:

1. Clone this repository to your local machine:
   ```bash
   git clone git@github.com:oumaima-aarabe/Minishell.git
   ```

2. Navigate into the project directory:
   ```bash
   cd Minishell
   ```

3. Build the project using `make`:
   ```bash
   make
   ```

4. Run Minishell:
   ```bash
   ./minishell
   ```

## Available Options

Minishell supports the following functionalities:

- **Command Execution**: Run executables from an absolute path, relative path, or environment PATH (e.g., `/bin/ls` or `ls`), including arguments or options.
- **Redirections**: Use `>`, `>>`, `<`, and `<<` for input/output redirection.
- **Pipes**: Chain commands using the `|` operator.
- **Environment Variables**: Handle environment variables like `$HOME` and access the return code with `$?`.
- **Signal Handling**: Use `Ctrl-C` to interrupt, `Ctrl-\` to quit, and `Ctrl-D` to send an EOF, similar to bash.

### Built-in Functions

Some functions are built-in, meaning they are implemented directly within Minishell:

- `echo` with the `-n` option
- `cd` with relative or absolute paths
- `pwd` with no options
- `export` with no options
- `unset` with no options
- `env` with no options or arguments
- `exit` with no options

---
