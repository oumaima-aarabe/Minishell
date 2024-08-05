# Minishell

## Introduction

Welcome to Minishell, a simplified Unix shell implementation written in C. Designed as part of the 42 curriculum, Minishell offers a command-line interface for interacting with the operating system, allowing users to execute commands and manage processes. This project aims to recreate the functionality of a bash-like shell, focusing on parsing prompts, launching executables with arguments, and incorporating several built-in functions.

## Final Grade

101/125


Adding an explanation of the project to the README can provide valuable context for readers, explaining the purpose, goals, and significance of the project. Here's how you could incorporate an explanation based on the provided sources:

---


## Goals and Significance

The primary goal of Minishell is to provide a hands-on experience in developing a command-line interface that allows users to interact with the operating system through typed commands. This project covers essential topics such as:

- **Process Management**: Understanding how to spawn child processes and manage their execution.
- **I/O Redirection and Piping**: Learning about the intricacies of redirecting input and output streams and implementing the ability to chain commands using pipes.
- **Signal Handling**: Gaining insight into how signals are handled in Unix-like systems, crucial for implementing graceful shutdowns and responding to user interrupts.
- **Environment Variables**: Exploring how to manipulate and utilize environment variables within the shell.
- **Built-in Commands**: Implementing a set of built-in commands that mimic the behavior of common Unix utilities, enhancing the usability and functionality of the shell.

By undertaking this project, participants not only develop a deeper appreciation for the Unix philosophy but also acquire practical skills in system-level programming. This project serves as a stepping stone towards more complex applications that interact closely with the operating system.

## Implementation Details

The implementation of Minishell involves several key components:

- **Parsing User Input**: Reading and interpreting user commands, including handling special characters and built-in commands.
- **Executing Commands**: Spawning child processes to execute commands and managing their lifecycle.
- **Input/Output Redirection**: Implementing the ability to redirect input and output streams, allowing users to control how commands read from and write to files.
- **Piping**: Supporting the chaining of commands using pipes, enabling complex workflows to be executed in a single line.
- **Signal Handling**: Capturing and responding to signals such as Ctrl+C and Ctrl+\ to gracefully terminate processes.
- **Environment Variables**: Parsing and manipulating environment variables, providing a mechanism for customizing the shell's behavior.

---
## Features

- **Command Execution**: Capable of executing external commands and displaying their output.
- **Input/Output Redirection**: Supports redirecting command input and output using `<`, `>`, and `>>` operators.
- **Heredoc**: Allows specifying a delimiter and inputting text until the delimiter is encountered.
- **Piping**: Enables chaining multiple commands together using the `|` operator.
- **Basic Environment Variables**: Includes setting and accessing basic environment variables.
- **Signal Handling**: Properly handles signals such as SIGINT (Ctrl+C) and SIGQUIT (Ctrl+\) for process termination.

## Getting Started

### Requirements

To build and run Minishell on macOS, ensure you have the GNU Readline library installed for command-line editing capabilities.

### Installing Dependencies on macOS

Follow these steps to install the necessary packages using Homebrew:

1. **Install Homebrew** (if not already installed):
    ```bash
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    ```
    Note: The link provided earlier seems to be outdated or incorrect. Please visit the official Homebrew website for the most current installation script.

2. **Install Readline**:
    ```bash
    brew install readline
    ```

### Setting Up the Project

Before proceeding, make sure you have the required dependencies installed.

To set up and run Minishell:

1. Clone the repository to your local machine:
   ```bash
   git clone git@github.com:oumaima-aarabe/Minishell.git
   ```

2. Change into the project directory:
   ```bash
   cd Minishell
   ```

3. Compile the project using `make`:
   ```bash
   make
   ```

4. Launch Minishell:
   ```bash
   ./minishell
   ```

## Available Options

Minishell supports various functionalities, including:

- **Command Execution**: Executes executables from an absolute path, relative path, or environment PATH, with support for arguments or options.
- **Redirections**: Utilizes `>`, `>>`, `<`, and `<<` for input/output redirection.
- **Pipes**: Chains commands using the `|` operator.
- **Environment Variables**: Manages environment variables like `$HOME` and accesses the return code with `$?`.
- **Signal Handling**: Interrupts with `Ctrl-C`, quits with `Ctrl-\`, and sends an EOF with `Ctrl-D`.

### Built-in Functions

Several functions are built directly into Minishell:

- `echo` with the `-n` option
- `cd` with relative or absolute paths
- `pwd` with no options
- `export` with no options
- `unset` with no options
- `env` with no options or arguments
- `exit` with no options

---
