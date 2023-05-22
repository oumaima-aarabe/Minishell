#include "Minishell.h"

Command *createCommandNode() 
{
    Command *node = (Command*)malloc(sizeof(Command));
    node->command = NULL;
    node->arguments = NULL;
    node->infile = NULL;
    node->outfile = NULL;
    node->pipe = 0;
    node->next = NULL;
    return node;
}

void freeCommandNode(Command    *node) 
{
    if (node == NULL)
        return;
    free(node->command);
    if (node->arguments != NULL) {
        int i = 0;
        while (node->arguments[i] != NULL) {
            free(node->arguments[i]);
            i++;
        }
        free(node->arguments);
    }
    free(node->infile);
    free(node->outfile);
    free(node);
}

void freeCommandTable(CommandTable  *table) 
{
    Command *current = table->head;
    while (current != NULL) {
        Command *temp = current;
        current = current->next;
        freeCommandNode(temp);
    }
    table->head = NULL;
}

void parsecommand(char  *input, CommandTable *table) 
{
    char    *inputCopy = strdup(input);
    char    *commandStr = strtok(inputCopy, "|");

    Command *prevCommand = NULL;

    while (commandStr != NULL) {
        Command *command = createCommandNode();
        command->pipe = 0;

        char    *argument;
        int argIndex = 0;
        int inQuote = 0;
        int argCount = 0;
        int argSize = 2;  // Start with space for two arguments (command and NULL terminator)

        command->command = strdup(strtok(commandStr, " \t\r\n"));
        command->arguments = (char**)malloc(argSize     *sizeof(char*));
        command->arguments[argIndex] = NULL;

        argument = strtok(NULL, " \t\r\n");

        while (argument != NULL) {
            if (inQuote) {
                int len = strlen(command->arguments[argIndex]);
                command->arguments[argIndex] = realloc(command->arguments[argIndex], len + strlen(argument) + 2);
                strcat(command->arguments[argIndex], " ");
                strcat(command->arguments[argIndex], argument);

                if (argument[strlen(argument) - 1] == '\'') {
                    inQuote = 0;
                    command->arguments[argIndex][strlen(command->arguments[argIndex]) - 1] = '\0';
                }
            } else {
                if (argument[0] == '\'') {
                    if (argument[strlen(argument) - 1] == '\'') {
                        command->arguments[argIndex] = strdup(&argument[1]);
                        command->arguments[argIndex][strlen(command->arguments[argIndex]) - 1] = '\0';
                    } else {
                        inQuote = 1;
                        command->arguments[argIndex] = strdup(&argument[1]);
                    }
                } else {
                    command->arguments[argIndex] = strdup(argument);
                }
            }

            argument = strtok(NULL, " \t\r\n");

            if (argCount + 1 >= argSize) {
                argSize *= 2;
                command->arguments = (char**)realloc(command->arguments, argSize    *sizeof(char*));
                command->arguments[argSize - 1] = NULL;
            }

            argIndex++;
            argCount++;
        }

        if (prevCommand == NULL) {
            table->head = command;
        } else {
            prevCommand->next = command;
        }

        prevCommand = command;

        commandStr = strtok(NULL, "|");
        if (commandStr != NULL) {
            command->pipe = 1; // Set pipe flag for commands preceding a pipe symbol
        }
    }

    free(inputCopy);
}


void executeCommands(const CommandTable *table) 
{
    Command *command = table->head;

    while (command ) {
        printf("Executing command: %s\n", command->command);
        printf("Arguments:");
        char*   *arg = command->arguments;
        while (*arg != NULL) {
            printf(" %s", *arg);
            arg++;
        }
        printf("\n");
        printf("Infile: %s\n", command->infile);
        printf("Outfile: %s\n", command->outfile);
        printf("Pipe: %d\n", command->pipe);
        printf("------\n");

        command = command->next;
    }
}

int main() 
{
    char    *pwd;
    char    *prompt;

    CommandTable table;
    table.head = NULL;

    while (1) {
        pwd = getcwd(NULL, 0);
        prompt = readline(strcat(pwd, " -> "));
        free(pwd);
        if (!prompt)
            exit(0);
        add_history(prompt);
        parsecommand(prompt, &table);
        executeCommands(&table);
        free(prompt);
    }

    freeCommandTable(&table);

    return 0;
}




