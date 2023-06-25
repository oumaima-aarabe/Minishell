#include "minishell.h"

bool is_quote(char c) 
{
    return (c == '\'' || c == '\"');
}


int get_fl(const char *str) 
{
    int length = 0;
    bool inside_quotes = false;
    char quote_type = '\0';

    while (str[length] != '\0') {
        if (str[length] == '\'' || str[length] == '\"') 
        {
            if (inside_quotes && quote_type == str[length]) 
            {
                inside_quotes = false;
                quote_type = '\0';
            }
            else if (!inside_quotes) 
            {
                inside_quotes = true;
                quote_type = str[length];
            }
        }
        else if (!inside_quotes && (str[length] == '<' || str[length] == '>'))
            break; // Stop at red operator

        length++;
    }

    return length;
}
char *get_redfilen(int *i, int *j, char **cmd_l, char *which_red) 
{
    char *file_name = NULL;
    int file_len = 0;

    if (strcmp(which_red, ">>") == 0) 
    {
        if (cmd_l[*i][*j + 2]) 
        {   
            file_len = get_fl(&cmd_l[*i][*j + 2]);
            file_name = strndup(&cmd_l[*i][*j + 2], file_len);
            *j += file_len;
        } 
        else if (cmd_l[*i + 1] && strlen(cmd_l[*i + 1]) > 0) 
        {
            *j = 0;
            file_len = get_fl(cmd_l[*i + 1]);
            file_name = strndup(cmd_l[*i + 1], file_len);
            *i += 1;
            *j += file_len;
            int d = *i;
            int z = *j;
            printf("in file( %d): (%d)\n", d, z);
        }
    } 
    else if (strcmp(which_red, ">") == 0) 
    {
        if (cmd_l[*i][*j + 1]) 
        {
            file_len = get_fl(&cmd_l[*i][*j + 1]);
            file_name = strndup(&cmd_l[*i][*j + 1], file_len);
            *j += file_len;
        }
         else if (cmd_l[*i + 1] && strlen(cmd_l[*i + 1]) > 0) 
         {
             *j = 0;
            file_len = get_fl(cmd_l[*i + 1]);
            file_name = strndup(cmd_l[*i + 1], file_len);
            *i += 1;
            *j += file_len;
        }
    }
     else if (strcmp(which_red, "<") == 0) 
     {
        if (cmd_l[*i][*j + 1])
        {
            file_len = get_fl(&cmd_l[*i][*j + 1]);
            file_name = strndup(&cmd_l[*i][*j + 1], file_len);
            *j += file_len;
        } 
        else if (cmd_l[*i + 1] && strlen(cmd_l[*i + 1]) > 0) 
        {
             *j = 0;
            file_len = get_fl(cmd_l[*i + 1]);
            file_name = strndup(cmd_l[*i + 1], file_len);
            *i += 1;
            *j += file_len;
        }
    }
    printf("fl:%s:\n", file_name);
    return file_name;
}

void red_append(splitnode **node, int *i, int *j, char **cmdl) 
{
    char *appfile = get_redfilen(i, j, cmdl, ">>");
    if (appfile) 
    {
        int fd = open(appfile, O_WRONLY | O_CREAT | O_APPEND, 0666);
        if (fd == -1)
            perror("Error opening output file");
        else 
        {
            if ((*node)->out != -1)
                close((*node)->out);
            (*node)->out = fd;
        }
        free(appfile);
    }
}

void red_input(splitnode **node, int *i, int *j, char **cmdl) 
{
    char *infile = get_redfilen(i, j, cmdl, "<");
    if (infile) 
    {
        int fd = open(infile, O_RDONLY);
        if (fd == -1)
            perror("Error opening input file");
        else 
        {
            if ((*node)->in != -1)
                close((*node)->in);
            (*node)->in = fd;
        }
        free(infile);
    }
}

void red_output(splitnode **node, int *i, int *j, char **cmdl) 
{
    char *outfile = get_redfilen(i, j, cmdl, ">");
    if (outfile) 
    {
        int fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1)
            perror("Error opening output file");
        else 
        {
            if ((*node)->out != -1)
                close((*node)->out);
            (*node)->out = fd;
        }
        free(outfile);
    }
}

void later() 
{
    return;
}

splitnode *handle_redirections(splitnode *node) 
{
    splitnode *current = node;
    // splitnode *new_head = NULL;
    // splitnode *new_tail = NULL;
    while (current != NULL) 
    {
        char **cmdl = current->splitdata;
        int i = 0;

        while (cmdl[i]) 
        {
            int j = 0;
            bool inside_quotes = false;

            while (cmdl[i][j]) 
            {
                if (!inside_quotes && !is_quote(cmdl[i][j])) 
                {
                    if (cmdl[i][j] == '<' && cmdl[i][j + 1] != '<')
                        red_input(&current, &i, &j, cmdl);
                    else if (cmdl[i][j] == '>' && cmdl[i][j + 1] != '>')
                        red_output(&current, &i, &j, cmdl);
                    else if (cmdl[i][j] == '>' && cmdl[i][j + 1] == '>')
                        red_append(&current, &i, &j, cmdl);
                    else if (cmdl[i][j] == '<' && cmdl[i][j + 1] == '<')
                        later();
                }
                
                if (is_quote(cmdl[i][j]))
                    inside_quotes = !inside_quotes;

                if (cmdl[i][j])
                    j++;
            }
            i++;
        }

        current = current->next;
    }

    return node;
}

splitnode* remove_redirections(splitnode* node)
{
    splitnode* new_list = NULL;
    splitnode* current = node;

    splitnode   *head = NULL;
    splitnode   *tail = NULL;

    while (current != NULL) 
    {
        int word_count = 0;
        char    **splitdata = split_string(current->splitdata, &word_count);
        splitnode   *new_node = create_split_node(splitdata, word_count);

        if (head == NULL) 
        {
            head = new_node;
            tail = head;
        } else 
        {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
        current = current->next;
    }

    return head;
}



