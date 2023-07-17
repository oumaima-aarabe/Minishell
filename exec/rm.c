/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 08:19:19 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/17 05:29:06 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

bool is_redirection(char ch) 
{
    return (ch == '<' || ch == '>');
}

char **splitget(int hr, t_splitnode *current)
{
    int wc;
    char **splitdata;

    splitdata = NULL;
    if (hr == 0)
    {
        if (current->in == -2 || current->out == -2)
            wc = 0;
        else
            wc = word_count(current->splitdata);
        if (wc)
            splitdata = newstring(current->splitdata, wc);
    }
    else if (hr == 1)
    {
        if (g_v.sig_flag)
            wc = 0;
        else
            wc =  wc_heredoc(current->splitdata);
            if (wc)
            splitdata = ns_heredoc(current->splitdata, wc);
    }
    return (splitdata);
}
t_splitnode   *remove_redirections(t_splitnode  *node, int hr)
{
    t_splitnode *current = node;
    t_splitnode   *head = NULL;
    t_splitnode   *tail = NULL;
    t_splitnode   *new_node;

    while (current != NULL) 
    {
            new_node = create_new_node(splitget(hr, current), current->in, current->out); 
            if (head == NULL) 
            {
                head = new_node;
                tail = head;
                if (g_v.sig_flag)
                {
                    g_v.sig_flag = 0;
                    return(head);
                }
            } 
            else 
            {
                tail->next = new_node;
                new_node->prev = tail;
                tail = new_node;
            }
        current = current->next;
    }
    return head;
}
/////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////

t_quote skip_red(t_quote cq, char **cmdl)
{
        if (!cq.ind && !cq.ins && !is_quote(cmdl[cq.i][cq.j])) 
        {
            if ((cmdl[cq.i][cq.j] == '<' && cmdl[cq.i][cq.j + 1] != '<') \
            || (cmdl[cq.i][cq.j] == '>' && cmdl[cq.i][cq.j + 1] != '>'))
            {
                if (cmdl[cq.i][cq.j + 1])
                cq.j +=   get_fl(&cmdl[cq.i][cq.j + 1]);
                else if (cmdl[cq.i + 1])
                cq.j = get_fl(cmdl[++(cq.i)]);
                return cq;
            }
            else if (cmdl[cq.i][cq.j] == '>' && cmdl[cq.i][cq.j + 1] == '>')
            {
                if (cmdl[cq.i][cq.j + 2])
                cq.j +=   get_fl(&cmdl[cq.i][cq.j + 2]) + 2;
                else if (cmdl[cq.i + 1])
                cq.j = get_fl(cmdl[++(cq.i)]);
                return cq;
            }
        }
    return (cq);
}

t_quote _check_printable(t_quote cq, char *cmdl, int n)
{
    cq = check_quotes(cq, cq.j, cmdl);
    if ((cq.ind || cq.ins) ||!is_redirection(cmdl[cq.j]))
    {
        cq.print = true;
        if(n)
        {   
            cq.z = cq.i;
            cq.count++;    
        }  
    }
    return(cq);
}
int word_count(char **cmdl)
{
        t_quote cq;
        ft_memset(&cq, 0, sizeof(t_quote));
    if (cmdl)
    {
        while (cmdl[cq.i]) 
        {
            cq.j = 0;
            while (cmdl[cq.i][cq.j]) 
            {
                cq = check_quotes(cq,cq.j, cmdl[cq.i]);
                if ((cq.ind || cq.ins) ||!is_redirection(cmdl[cq.i][cq.j]))
                    cq.print = true;
                cq = skip_red(cq, cmdl);
                if (cmdl[cq.i][cq.j])
                    cq.j++;
            }
            if (cq.print)
            {
                cq.wc++;
                cq.print = false;
            }
            cq.i++;
        }
    }
    return (cq.wc);
}

/////////////////////////////////////////////////////////

char **newstring(char **cmdl, int wc)
{
    char **new_s;
    int i = 0;
    int j;
    int count = 0;
    bool print = false;
    int k = 0;
    int z;
    t_quote cq;

    new_s = (char **)ft_calloc((wc + 1) , sizeof(char *));
    while (cmdl[i] && k < wc) 
    {
        j = 0;
        ft_memset(&cq, 0, sizeof(t_quote));
        while (cmdl[i][j]) 
        {
            cq = check_quotes(cq,j, cmdl[i]);
            if ((cq.ind || cq.ins) || !is_redirection(cmdl[i][j]))
            {
                print = true;
                z = i;
                count++;
            }
            if (!cq.ind && !cq.ins && !is_quote(cmdl[i][j])) 
            {
                if (cmdl[i][j] == '<' && cmdl[i][j + 1] != '<')
                {
                    if (cmdl[i][j + 1])
                    j +=   get_fl(&cmdl[i][j + 1]) + 1;
                    else if (cmdl[i + 1])
                    j = get_fl(cmdl[++i]);
                    continue;
                }
                else if (cmdl[i][j] == '>' && cmdl[i][j + 1] != '>')
                {
                    if (cmdl[i][j + 1])
                    j +=   get_fl(&cmdl[i][j + 1]) + 1;
                    else if (cmdl[i + 1])
                    j = get_fl(cmdl[++i]);
                    continue;
                }
                else if (cmdl[i][j] == '>' && cmdl[i][j + 1] == '>')
                {
                    if (cmdl[i][j + 2])
                    j +=   get_fl(&cmdl[i][j + 2]) + 2;
                    else if (cmdl[i + 1])
                    j = get_fl(cmdl[++i]);
                    continue;
                }
            }
            if (cmdl[i][j])
                j++;
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
            k++;
            print = false;
            count = 0;
        }
        i++;
    }
        return new_s;
}
/////////////////////////////////////////////////////////
