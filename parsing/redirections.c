/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 21:14:41 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/06/14 01:50:09 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *get_redfilen(char **command_line, char *redirection_symbol)
{
    char    *symbol_position = strstr(command_line, redirection_symbol);
    if (symbol_position == NULL)
        return NULL;
        // Redirection symbol not found

    // Calculate the start position of the file name
    char    *file_start = symbol_position + strlen(redirection_symbol);
    while (*file_start != '\0' && (*file_start == ' ' || *file_start == '\t'))
        file_start++; // Skip leading whitespace

    // Find the end position of the file name
    char    *file_end = file_start;
    while (*file_end != '\0' && *file_end != ' ' && *file_end != '\t' && *file_end != '\n')
        file_end++;

    // Calculate the length of the file name
    size_t file_length = file_end - file_start;

    // Allocate memory for the file name and copy it
    char    *file_name = (char*)malloc((file_length + 1) * sizeof(char));
    strncpy(file_name, file_start, file_length);
    file_name[file_length] = '\0';

    return file_name;
}

void    red_append(splitnode *node, int *i, int *j, char **cmdl)
{
    char *appfile = get_redfilen(cmdl[*i], ">>");
    node->out = open(appfile, O_WRONLY | O_CREAT | O_APPEND, 0666);
}

void    red_input(splitnode *node, int *i, int *j, char **cmdl)
{
    char *infile = get_redfilen(cmdl[*i], "<");
    node->in = open(infile, O_RDONLY);
}

void    red_output(splitnode *node, int *i, int *j, char **cmdl)
{
    char *outfile = get_redfilen(cmdl[*i], ">");
    node->out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    
}
//----------------------------------------------------------------//
//later for heredoc
void later()
{

}
////////////////////////////////////////////////////////////////
void    handle_redirections(splitnode *node)
{
    char **cmdl;
    int i = 0;
    int j;

    while(node)
    {
        initial(node);
        cmdl = node->splitdata;
        i = 0;
        while (cmdl[i])
        {
            j = 0;
            while(cmdl[i][j])
            {
                if (cmdl[i][j] == '<' && cmdl[i][j + 1] != '<')
                    red_input(node, &i, &j, cmdl);
                else if (cmdl[i][j] == '<' && cmdl[i][j + 1] == '<')
                    later();
                else if (cmdl[i][j] == '>' && cmdl[i][j + 1] != '>')
                    red_output(node, &i, &j, cmdl);
                else if (cmdl[i][j] == '>' && cmdl[i][j + 1] == '>')
                    red_append(node, &i, &j, cmdl);
                else
                    j++;
            }
            i++;
        }
        node = node->next;
    }
}