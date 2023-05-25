/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 00:50:32 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/05/23 01:03:02 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Global variable to store the exit status of the most recently executed foreground pipeline
int last_exit_status = 0;

// Function to handle the SIGINT signal (ctrl-C)
void sigint_handler(int sig) {
    // Display a new prompt on a new line
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

// Function to handle the SIGQUIT signal (ctrl-\)
void sigquit_handler(int sig) {
    // Do nothing
}

// Function to create a new command node
struct CommandNode* create_command_node(char* command) {
    struct CommandNode* node = (struct CommandNode*)malloc(sizeof(struct CommandNode));
    node->command = strdup(command);
    node->prev = NULL;
    node->next = NULL;
    return node;
}

// Function to add a command to the history
void add_to_history(struct ShellState* state, char* command) {
    struct CommandNode* node = create_command_node(command);
    if (state->history_head == NULL) {
        state->history_head = node;
        state->history_tail = node;
    } else {
        node->prev = state->history_tail;
        state->history_tail->next = node;
        state->history_tail = node;
    }
}

// Function to free the memory allocated for the command history
void free_history(struct ShellState* state) {
    struct CommandNode* current = state->history_head;
    while (current != NULL) {
        struct CommandNode* next = current->next;
        free(current->command);
        free(current);
        current = next;
    }
}

// Function to execute a command
void execute_command(char** args) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return;
    } else if (pid == 0) {
        // Child process
        execvp(args[0], args);
        perror("execvp");
        exit(1);
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
        last_exit_status = WEXITSTATUS(status);
    }
}

// Function to handle built-in commands
int handle_builtin_command(struct ShellState* state, char** args) {
    if (strcmp(args[0], "exit") == 0) {
        free_history(state);
        exit(0);
    } else if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL) {
            fprintf(stderr, "cd: missing argument\n");
        } else if (chdir(args[1]) != 0) {
            perror("cd");
        }
        return 1;
    } else if (strcmp(args[0], "pwd") == 0) {
        char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("%s\n", cwd);
        } else {
            perror("getcwd");
        }
        return 1;
    } else if (strcmp(args[0], "echo") == 0) {
        int i = 1;
        while (args[i] != NULL) {
            printf("%s ", args[i]);
            i++;
        }
        printf("\n");
        return 1;
    } else if (strcmp(args[0], "export") == 0) {
        if (args[1] == NULL) {
            fprintf(stderr, "export: missing argument\n");
        } else {
            if (putenv(args[1]) != 0) {
                perror("export");
            }
        }
        return 1;
    } else if (strcmp(args[0], "unset") == 0) {
        if (args[1] == NULL) {
            fprintf(stderr, "unset: missing argument\n");
        } else {
            if (unsetenv(args[1]) != 0) {
                perror("unset");
            }
        }
        return 1;
    } else if (strcmp(args[0], "history") == 0) {
        struct CommandNode* current = state->history_head;
        int count = 1;
        while (current != NULL) {
            printf("%d. %s\n", count, current->command);
            current = current->next;
            count++;
        }
        return 1;
    }

    return 0;
}

// Function to read a line from input
char* read_line() {
    char* line = readline("shell> ");
    if (line == NULL) {
        // EOF (ctrl-D) encountered
        printf("\n");
        exit(0);
    }
    return line;
}

// Function to tokenize a line into arguments
void tokenize_line(char* line, char** args) {
    char* token;
    int arg_count = 0;
    token = strtok(line, " \t\n");
    while (token != NULL) {
        args[arg_count] = strdup(token);
        arg_count++;
        token = strtok(NULL, " \t\n");
    }
    args[arg_count] = NULL;
}

// Recursive function to execute commands
void execute_commands(struct ShellState* state) {
    char* line = read_line();
    add_to_history(state, line);

    char** args = (char**)malloc(sizeof(char*) * MAX_ARGS);
    tokenize_line(line, args);

    if (args[0] != NULL) {
        if (!handle_builtin_command(state, args)) {
            execute_command(args);
        }
    }

    free(line);
    free(args);
    execute_commands(state);
}

int main() {
    // Initialize the shell state
    struct ShellState state;
    state.history_head = NULL;
    state.history_tail = NULL;

    // Set up signal handlers
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, sigquit_handler);

    // Start executing commands
    execute_commands(&state);

    return 0;
}
