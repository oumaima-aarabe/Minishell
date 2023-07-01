/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 00:19:49 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/01 04:14:57 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_gs	g_v;

void parsing(char* prompt, t_env *env) 
{
    Node* node = splitstring(prompt);
    splitnode* tokens = splitdatalinkedlist(node);
    freenodes(node);

    tokens = handle_redirections(tokens, env);
    splitnode *current = tokens;
    while (current != NULL) 
    {
        splitnode* next = current->next;

        // Print the split data
        int i = 0;
        while (current->splitdata[i]) 
        {
            printf("Token %d: .%s.\n", i + 1, current->splitdata[i]);
            i++;
        }
        printf("red : %d||%d\n", current->in, current->out);
        // Free the split data
        i = 0;
        while (current->splitdata[i] != NULL) 
        {
            free(current->splitdata[i]);
            i++;
        }
        free(current->splitdata);

        free(current);

        current = next;
    }
}
