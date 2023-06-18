/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 21:14:46 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/05/25 01:17:46 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    handle_pipe(s_tokens *tokens, char *prompt, int *i)
{
    int j;
    char    *cmd;
    
    j = -1;
    cmd = malloc(i + 1); 
    while (++j < i)
        cmd[j] = *prompt++;
    cmd[j] = '\0';
    tokens = new_node(NULL);
    tokens->left = new_node(cmd);
}