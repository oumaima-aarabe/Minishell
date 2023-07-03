/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 22:46:07 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/03 09:59:59 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

t_gs	g_v;

char	**apply_ex_q(char **splitdata, t_env *en)
{
	int		i;
	char	*expanded;
	char	*quotesremoved;

	i = 0;
	while (splitdata[i])
	{
		expanded = ft_expand(splitdata[i], en);
		splitdata[i] = expanded;
		quotesremoved = removequotes(splitdata[i]);
		splitdata[i] = quotesremoved;
		i++;
	}
	return (splitdata);
}

t_splitnode	*iteratelist(t_splitnode *head, t_env *en)
{
	t_splitnode	*current;
	char		**splitdata;

	current = head;
	while (current != NULL)
	{
		splitdata = current->splitdata;
		splitdata = apply_ex_q(splitdata, en);
		current = current->next;
	}
	return (head);
}

t_splitnode	*parsing(char	*prompt, t_env *env)
{
	t_Node		*node;
	t_splitnode	*tokens;

	node = splitstring(prompt);
	tokens = splitdatalinkedlist(node);
	freenodes(node);
	tokens = handle_redirections(tokens, env);
	iteratelist(tokens, env);
	return (tokens);
}
