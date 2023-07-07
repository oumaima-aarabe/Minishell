/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 08:19:19 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/03 09:02:14 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

bool is_redirection(char ch) 
{
    return (ch == '<' || ch == '>');
}

t_splitnode   *remove_redirections(t_splitnode  *node)
{
    t_splitnode *current = node;
    char **splitdata = NULL;

    t_splitnode   *head = NULL;
    t_splitnode   *tail = NULL;

    while (current != NULL) 
    {
        splitdata = newstring(current->splitdata, word_count(current->splitdata));
        t_splitnode   *new_node = create_new_node(splitdata, current->in, current->out);

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

t_splitnode   *create_new_node(char   **splitdata, int in, int out) 
{
    t_splitnode   *new_split_node = calloc(1, sizeof(t_splitnode));
    new_split_node->splitdata = splitdata;
    new_split_node->prev = NULL;
    new_split_node->next = NULL;
    new_split_node->in = in;
    new_split_node->out = out;
    return new_split_node;
}

int word_count(char **cmdl)
{
        int i = 0;
        int wc = 0;
        bool print = false;

        while (cmdl[i]) 
        {
            int j = 0;
            bool inside_quotes = false;
            while (cmdl[i][j]) 
            {
                if (!is_redirection(cmdl[i][j]))
                    print = true;
                if (!inside_quotes && !is_quote(cmdl[i][j])) 
                {
                    if (cmdl[i][j] == '<' && cmdl[i][j + 1] != '<')
                    {
                        if (cmdl[i][j + 1])
                        j +=   get_fl(&cmdl[i][j + 1]);
                        else if (cmdl[i + 1])
                        j = get_fl(cmdl[++i]);
                    }
                    else if (cmdl[i][j] == '>' && cmdl[i][j + 1] != '>')
                    {
                        if (cmdl[i][j + 1])
                        j +=   get_fl(&cmdl[i][j + 1]);
                        else if (cmdl[i + 1])
                        j = get_fl(cmdl[++i]);
                    }
                    else if (cmdl[i][j] == '>' && cmdl[i][j + 1] == '>')
                    {
                        if (cmdl[i][j + 2])
                        j +=   get_fl(&cmdl[i][j + 2]) + 1;
                        else if (cmdl[i + 1])
                        j = get_fl(cmdl[++i]);
                    }
                    else if (cmdl[i][j] == '<' && cmdl[i][j + 1] == '<')
                        {if (cmdl[i][j + 2])
                        j +=   get_fl(&cmdl[i][j + 2]) + 1;
                        else if (cmdl[i + 1])
                        j = get_fl(cmdl[++i]);}
                }
                
                if (is_quote(cmdl[i][j]))
                    inside_quotes = !inside_quotes;
                if (cmdl[i][j])
                    j++;
            }
            if (print)
            {
                wc++;
                print = false;
            }
            i++;
        }
        return (wc);
}

char **newstring(char **cmdl, int wc)
{
    char **new_s;
    int i = 0;
    int j;
    int count = 0;
    bool print = false;
    int k = 0;
    int z;

    
    new_s = (char **)ft_calloc((wc + 1) , sizeof(char *));
     while (cmdl[i] && i < wc) 
    {
        j = 0;
        bool inside_quotes = false;
        while (cmdl[i][j]) 
        {
            if (inside_quotes || !is_redirection(cmdl[i][j]))
            {
                print = true;
                z = i;
                count++;
            }
            if (!inside_quotes && !is_quote(cmdl[i][j])) 
            {
                if (cmdl[i][j] == '<' && cmdl[i][j + 1] != '<')
                {
                    if (cmdl[i][j + 1])
                    j +=   get_fl(&cmdl[i][j + 1]);
                    else if (cmdl[i + 1])
                    j = get_fl(cmdl[++i]);
                }
                else if (cmdl[i][j] == '>' && cmdl[i][j + 1] != '>')
                {
                    if (cmdl[i][j + 1])
                    j +=   get_fl(&cmdl[i][j + 1]);
                    else if (cmdl[i + 1])
                    j = get_fl(cmdl[++i]);
                }
                else if (cmdl[i][j] == '>' && cmdl[i][j + 1] == '>')
                {
                    if (cmdl[i][j + 2])
                    j +=   get_fl(&cmdl[i][j + 2]) + 1;
                    else if (cmdl[i + 1])
                    j = get_fl(cmdl[++i]);
                }
                else if (cmdl[i][j] == '<' && cmdl[i][j + 1] == '<')
                   {
                    if (cmdl[i][j + 2])
                    j +=   get_fl(&cmdl[i][j + 2]) + 1;
                    else if (cmdl[i + 1])
                    j = get_fl(cmdl[++i]);
                }
            }
            if (cmdl[i][j])
            {
                if (is_quote(cmdl[i][j]))
                    inside_quotes = !inside_quotes;
                j++;
            }
        }
        if (print)
        {
            new_s[k] = (char *)ft_calloc((count + 1) , sizeof(char ));
            j = 0;
            while (j < count)
            {
                new_s[k][j] = cmdl[z][j];
                j++;
            }
            new_s[k][j] = '\0';
            k++;
            print = false;
            count = 0;
        }
        i++;
    }
        return new_s;
}