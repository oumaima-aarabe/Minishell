/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 07:32:30 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/19 03:50:07 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

bool	is_redirection(char ch)
{
	return (ch == '<' || ch == '>');
}
t_hd	new_wc(char **cmdl, t_hd hd)
{
	if(hd.print)
	{
		hd.wc++;
		hd.print = 0;
	}
	hd.j = get_fl(cmdl[++hd.i]);
	return(hd);
}

t_hd	check_dprintable(char **cmdl, t_quote cq, t_hd hd)
{
	if ((cq.ind || cq.ins) || ft_strncmp("<<", &cmdl[hd.i][hd.j], 2))
		hd.print = 1;
	if (!cq.ind && !cq.ins && !is_quote(cmdl[hd.i][hd.j]))
	{
		if (cmdl[hd.i][hd.j] == '<' && cmdl[hd.i][hd.j + 1] == '<')
		{
			if (cmdl[hd.i][hd.j + 2])
				hd.j += get_fl(&cmdl[hd.i][hd.j + 2]) + 2;
			else if (cmdl[hd.i + 1])
				hd = new_wc(cmdl, hd);
			return (hd);
		}
	}
	if (cmdl[hd.i][hd.j])
	{
		if (is_quote(cmdl[hd.i][hd.j]))
			cq = check_quotes(cq, hd.j, cmdl[hd.i]);
		hd.j++;
	}
	return (hd);
}

char	*fill_ns(t_quote *cq, char **cmdl)
{
	char	*new_s;

	new_s = NULL;
	new_s = (char *)ft_calloc((cq->count + 1), sizeof(char ));
	if (!new_s)
		return (NULL);
	cq->j = 0;
	while (cq->j < cq->count)
	{
		new_s[cq->j] = cmdl[cq->z][cq->j];
		cq->j++;
	}
	cq->print = 0;
	cq->count = 0;
	return (new_s);
}

char	**newstring(char **cmdl, int wc)
{
	char	**new_s;
	t_quote	cq;

	ft_memset(&cq, 0, sizeof(t_quote));
	new_s = (char **)ft_calloc((wc + 1), sizeof(char *));
	while (new_s && cmdl[cq.i] && cq.length < wc)
	{
		cq.j = 0;
		while (cmdl[cq.i][cq.j])
		{
			cq = check_quotes(cq, cq.j, cmdl[cq.i]);
			if ((cq.ind || cq.ins) || !is_redirection(cmdl[cq.i][cq.j]))
			{
				cq.print = true;
				cq.z = cq.i;
				cq.count++;
			}
			cq = skip_red(cq, cmdl);
		}
		if (cq.print)
			new_s[cq.length++] = fill_ns(&cq, cmdl);
		cq.i++;
	}
	return (new_s);
}
