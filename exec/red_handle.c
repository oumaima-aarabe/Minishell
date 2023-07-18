/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 07:19:12 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/18 07:21:48 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	get_fl( char *str)
{
	int		length;
	t_quote	cq;

	length = 0;
	ft_memset(&cq, 0, sizeof(t_quote));
	while (str[length])
	{
		cq = check_quotes(cq, length, str);
		if (!cq.ind && !cq.ins && (str[length] == '<' || str[length] == '>'))
			break ;// Stop at red operator
		if (str[length])
			length++;
	}
	return (length);
}

void	hr_loop(t_splitnode *c, t_quote cq, t_env *env, int *i)
{
	while (c->splitdata[*i][cq.j] && !g_v.red_flag)
	{
		cq = check_quotes(cq,cq.j, c->splitdata[*i]);
		if (!cq.ind && !cq.ins && !is_quote(c->splitdata[*i][cq.j]))
		{
			if (c->splitdata[*i][cq.j] == '<' && c->splitdata[*i][cq.j + 1] != '<')
			{
				red_input(&c, i, &cq.j, env);
				continue ;
			}
			else if (c->splitdata[*i][cq.j] == '>' && c->splitdata[*i][cq.j + 1] != '>')
			{
				red_output(&c, i, &cq.j, env);
				continue ;
			}
			else if (c->splitdata[*i][cq.j] == '>' && c->splitdata[*i][cq.j + 1] == '>')
			{
				red_append(&c, i, &cq.j, env);
				continue ;
			}
		}
			cq.j++;
	}
}

void	hh_loop(t_splitnode *c, t_env *env)
{
	int		i;
	int		j;
	t_quote	cq;

	i = 0;
	while (c->splitdata[i])
	{
		j = 0;
		ft_memset(&cq, 0, sizeof(t_quote));
		while (c->splitdata[i][j])
		{
			cq = check_quotes(cq, j, c->splitdata[i]);
			if (!cq.ind && !cq.ins && !is_quote(c->splitdata[i][j]))
				if (c->splitdata[i][j] == '<' && c->splitdata[i][j + 1] == '<')
				{
					c = read_hd(c, &i, &j, env);
					continue ;
				}
			if (c->splitdata[i][j])
				j++;
		}
		if (c->splitdata[i])
			i++;
	}
}

t_splitnode	*handle_heredoc(t_splitnode *node, t_env *env)
{
	t_splitnode	*c;
	t_splitnode	*trimmed;

	c = node;
	while (c != NULL)
	{
		hh_loop(c, env);
		c = c->next;
	}
	trimmed = remove_redirections(node, 1);
	free_split_nodes(node);
	return (trimmed);
}

t_splitnode	*handle_redirections(t_splitnode *node, t_env *env)
{
	t_splitnode	*current;
	t_splitnode	*trimmed;
	t_quote		cq;
	int			i;

	current = node;
	trimmed = NULL;
	while (current != NULL)
	{
		g_v.red_flag = 0;
		i = 0;
		if (current->splitdata)
		{
			while (current->splitdata[i] && !g_v.red_flag)
			{
				ft_memset(&cq, 0, sizeof(t_quote));
				hr_loop(current, cq, env, &i);
				i++;
			}
		}
		current = current->next;
	}
	trimmed = remove_redirections(node, 0);
	free_split_nodes(node);
	return (trimmed);
}