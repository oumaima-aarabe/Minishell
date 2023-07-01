/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 22:46:07 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/06/22 19:38:06 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

t_gs	g_v;

splitnode   *parsing(char* prompt, t_env *env)
{
    Node* node = splitstring(prompt);
    splitnode* tokens = splitdatalinkedlist(node);
    freenodes(node);

    tokens = handle_redirections(tokens, env);
   
    return(tokens);
}