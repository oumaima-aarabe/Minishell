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

char    *get_redfilen(int i, int j, char    **cmd_l, char   *which_red) 
{
    char    *file_name = NULL;
    if (cmd_l[i][j] && cmd_l[i][j + 1] && strcmp(&cmd_l[i][j], which_red) == 0) 
    {
        if (cmd_l[i][j + 2])
            file_name = strdup(&cmd_l[i][j + 2]);
        else if (cmd_l[i + 1])
            file_name = strdup(cmd_l[i + 1]);
    }
    return file_name;
}

void red_append(splitnode   *node, int i, int j, char **cmdl)
 {
    char    *appfile = get_redfilen(i, j, cmdl, ">>");
    if (appfile)
     {
        if (node->out != -1)
            close(node->out);
        node->out = open(appfile, O_WRONLY | O_CREAT | O_APPEND, 0666);
        free(appfile);
    }
}

void red_input(splitnode    *node, int i, int j, char  **cmdl) {
    char    *infile = get_redfilen(i, j, cmdl, "<");
    if (infile)
    {
        if (node->in != -1)
            close(node->in);
        node->in = open(infile, O_RDONLY);
        free(infile);
    }
}

void red_output(splitnode   *node, int i, int j, char **cmdl) {
    char    *outfile = get_redfilen(i, j, cmdl, ">");
    if (outfile) 
    {
        if (node->out != -1)
            close(node->out);
        node->out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        free(outfile);
    }
}

void handle_redirections(splitnode  *node) {
    char    **cmdl;
    int i = 0;
    int j;

    while (node) 
    {
        cmdl = node->splitdata;
        i = 0;
        while (cmdl[i]) 
        {
            j = 0;
            while (cmdl[i][j])
             {
                if (cmdl[i] && cmdl[i][j] && cmdl[i][j] == '<' && cmdl[i][j + 1] != '<')
                    red_input(node, i, j, cmdl);
                else if (cmdl[i] && cmdl[i][j] && cmdl[i][j] == '<' && cmdl[i][j + 1] == '<')
                    later();
                else if (cmdl[i] && cmdl[i][j] && cmdl[i][j] == '>' && cmdl[i][j + 1] != '>')
                    red_output(node, i, j, cmdl);
                else if (cmdl[i] && cmdl[i][j] && cmdl[i][j] == '>' && cmdl[i][j + 1] == '>')
                    red_append(node, i, j, cmdl);
                else
                    j++;
            }
            i++;
        }
        node = node->next;
    }
}
