/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 22:46:07 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/03 08:20:17 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

t_gs	g_v;

char **apply_ex_q(char **splitdata, t_env *en) 
{
    int i;
    
    i = 0;
    while(splitdata[i]) 
    {
        char *expanded = ft_expand(splitdata[i], en);
        splitdata[i] = expanded;
        char *quotesRemoved = removequotes(splitdata[i]);
        splitdata[i] = quotesRemoved;
        i++;
    }
    return (splitdata);
}

splitnode *iteratelist(splitnode *head, t_env *en) 
{
    splitnode *current = head;
    while (current != NULL) 
    {
        char **splitdata = current->splitdata;
        
        splitdata = apply_ex_q(splitdata, en);
        
        current = current->next;
    }
    return (head);
}

splitnode   *parsing(char* prompt, t_env *env)
{
    Node* node = splitstring(prompt);
    splitnode* tokens = splitdatalinkedlist(node);
    freenodes(node);

    tokens = handle_redirections(tokens, env);
    iteratelist(tokens, env);
   
    return(tokens);
}