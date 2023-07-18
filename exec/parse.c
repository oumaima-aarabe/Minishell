/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 22:46:07 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/18 03:24:07 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	check_for_space(char *expanded)
{
	t_quote	cq;
	int		i;

	i = 0;
	ft_memset(&cq, 0, sizeof(t_quote));
	while (expanded[i])
	{
		cq = check_quotes(cq, i, expanded);
		if (!cq.ind && !cq.ins && expanded[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

char	**apply_q(char **splitdata)
{
	t_spex	spex;

	ft_memset(&spex, 0, sizeof(t_spex));
	while (splitdata[spex.i])
	{
		spex.quotesremoved = removequotes(splitdata[spex.i]);
		splitdata[spex.i] = spex.quotesremoved;
		spex.i++;
	}
	return (splitdata);
}

char	**apply_ex_q(char **splitdata, t_env *en)
{
	t_spex	spex;
	t_quote	cq;

	ft_memset(&cq, 0, sizeof(t_quote));
	ft_memset(&spex, 0, sizeof(t_spex));
	if (splitdata)
	{
		while (splitdata[spex.i])
		{
			spex.expanded = ft_expand(splitdata[spex.i], en);
			splitdata[spex.i] = spex.expanded;
			if (check_for_space(spex.expanded))
			{
				spex.splitted = split_string(spex.expanded, cq);
				spex.k = ft_double_strlen(spex.splitted);
				splitdata = ft_joindstrs_at(splitdata, \
				spex.splitted, spex.i);
				spex.i += spex.k;
			}
			if (splitdata[spex.i])
				spex.i++;
		}
		splitdata = apply_q(splitdata);
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
		current->splitdata = splitdata;
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
	tokens = handle_heredoc(tokens, env);
	tokens = handle_redirections(tokens, env);
	iteratelist(tokens, env);
	return (tokens);
}
