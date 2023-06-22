#include "minishell.h"

bool is_quote(char c) 
{
    return (c == '\'' || c == '\"');
}

char    *get_redfilen(int i, int j, char   **cmd_l, char    *which_red) 
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

void red_input(splitnode    *node, int i, int j, char  **cmdl) 
{
    char    *infile = get_redfilen(i, j, cmdl, "<");
    if (infile) 
    {
        if (node->in != -1)
            close(node->in);
        node->in = open(infile, O_RDONLY);
        free(infile);
    }
}

void red_output(splitnode   *node, int i, int j, char **cmdl) 
{
    char    *outfile = get_redfilen(i, j, cmdl, ">");
    if (outfile) 
    {
        if (node->out != -1)
            close(node->out);
        node->out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        free(outfile);
    }
}

void remove_redirections(splitnode  *node) 
{
    while (node) 
    {
        char    **cmdl = node->splitdata;
        int i = 0;

        while (cmdl[i]) 
        {
            char    *cmd = cmdl[i];
            int j = 0;
            int k = 0;
            bool inside_quotes = false;  // Flag to track if inside quotes or double quotes

            while (cmd[j]) 
            {
                if (!inside_quotes && (cmd[j] == '<' || cmd[j] == '>')) 
                {
                    j++;
                    if (cmd[j] == '>')
                        j++;
                    char    *file_name = get_redfilen(i, j, cmdl, "");
                    if (file_name) 
                    {
                        j += strlen(file_name);
                        free(file_name);
                    }
                } 
                else 
                {
                    cmd[k++] = cmd[j++];
                    if (is_quote(cmd[j - 1]))
                        inside_quotes = !inside_quotes;  // Toggle the inside quotes flag
                }
            }
            cmd[k] = '\0';
            i++;
        }
        node = node->prev;  // Move to the previous node in the linked list
    }
}


void later() 
{
    return;
}

splitnode   *handle_redirections(splitnode *node) 
{
    char    **cmdl;
    int i = 0;
    int j;

    while (node) {
        cmdl = node->splitdata;
        i = 0;

        while (cmdl[i]) 
        {
            j = 0;
            bool inside_quotes = false;  // Flag to track if inside quotes or double quotes

            while (cmdl[i][j]) 
            {
                if (!inside_quotes && !is_quote(cmdl[i][j])) 
                {
                    if (cmdl[i] && cmdl[i][j] && cmdl[i][j] == '<' && cmdl[i][j + 1] != '<')
                        red_input(node, i, j, cmdl);
                    else if (cmdl[i] && cmdl[i][j] && cmdl[i][j] == '<' && cmdl[i][j + 1] == '<')
                        later();
                    else if (cmdl[i] && cmdl[i][j] && cmdl[i][j] == '>' && cmdl[i][j + 1] != '>')
                        red_output(node, i, j, cmdl);
                    else if (cmdl[i] && cmdl[i][j] && cmdl[i][j] == '>' && cmdl[i][j + 1] == '>')
                        red_append(node, i, j, cmdl);
                }

                if (is_quote(cmdl[i][j]))
                    inside_quotes = !inside_quotes;  // Toggle the inside quotes flag
                j++;
            }
            i++;
        }
        node = node->next;
    }
        // remove_redirections(node);
    return node;
}


