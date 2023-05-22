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

void freeCommandNode(Command *node) 
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
    arg_t  *arg;
    Command *prevCommand = NULL;

    while (commandStr != NULL) 
    {   
        Command *command = init_arg(arg, inputCopy, commandStr);
        while (arg->argument != NULL) 
            args_parse(arg, command);
        if (prevCommand == NULL)
            table->head = command;
        else
            prevCommand->next = command;
        prevCommand = command;
        commandStr = strtok(NULL, "|");
        if (commandStr != NULL)
            command->pipe = 1; // Set pipe flag for commands preceding a pipe symbol
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



