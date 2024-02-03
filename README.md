Project 42 involves rewriting a personal bash script—an application designed to parse prompts, launch executables with arguments, and include a selection of built-in functions.


Minishell offers the following features:

Executables can be run from an absolute, relative, or environment PATH (/bin/ls or ls) with support for arguments or options. Both single (') and double (") quotes function similarly to bash, except for multiline commands.

Commands can be separated by space. Redirections (> >> <) and pipes (|) are supported.

Environment variables, such as $HOME, and the return code ($?) are handled seamlessly.

Interrupting a program is possible using Ctrl-C, quitting with Ctrl-, and triggering an EOF with Ctrl-D, similar to bash.

The inclusion of heredoc allows for convenient input stream redirection.

Several functions are 'built-in,' meaning the executables are recoded directly. This includes echo, pwd, cd, env, export, unset, and exit.
