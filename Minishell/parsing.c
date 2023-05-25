/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:38:29 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/05/22 15:55:56 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

Command    *init_arg(arg_t *arg, char *inputCopy, char *commandStr)
{
    Command *command = createCommandNode();
        command->pipe = 0;

        arg->argument;
        arg->argIndex = 0;
        arg->inQuote = 0;
        arg->argCount = 0;
        arg->argSize = 2;  // Start with space for two arguments (command and NULL terminator)

        command->command = strdup(strtok(commandStr, " \t\r\n"));
        command->arguments = (char**)malloc(arg->argSize * sizeof(char*));
        command->arguments[arg->argIndex] = NULL;

        arg->argument = strtok(NULL, " \t\r\n");
        return (command);
}


void    args_parse(arg_t *arg, Command *command )
{
   
    while (arg->argument != NULL) 
    {
        if (arg->inQuote) {
            int len = strlen(command->arguments->content[arg->argIndex]);
            command->arguments[arg->argIndex] = realloc(command->arguments[arg->argIndex], len + strlen(arg->argument) + 2);
            strcat(command->arguments[arg->argIndex], " ");
            strcat(command->arguments[arg->argIndex], arg->argument);

            if (arg->argument[strlen(arg->argument) - 1] == '\'') {
                arg->inQuote = 0;
                command->arguments[arg->argIndex][strlen(command->arguments[arg->argIndex]) - 1] = '\0';
            }
        } 
        else 
        {
            if (arg->argument[0] == '\'') 
            {
                if (arg->argument[strlen(arg->argument) - 1] == '\'') 
                {
                    command->arguments[arg->argIndex] = strdup(&arg->argument[1]);
                    command->arguments[arg->argIndex][strlen(command->arguments[arg->argIndex]) - 1] = '\0';
                }
                else 
                {
                    arg->inQuote = 1;
                    command->arguments[arg->argIndex] = strdup(&arg->argument[1]);
                }
            } 
            else 
                command->arguments[arg->argIndex] = strdup(arg->argument);
        }

        arg->argument = strtok(NULL, " \t\r\n");

        if (arg->argCount + 1 >= arg->argSize) {
            arg->argSize *= 2;
            command->arguments = (char**)realloc(command->arguments, arg->argSize    *sizeof(char*));
            command->arguments[arg->argSize - 1] = NULL;
        }

        arg->argIndex++;
        arg->argCount++;
        }
}
