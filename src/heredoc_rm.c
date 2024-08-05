/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_rm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 07:16:37 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/19 05:36:46 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

t_hd	numerate(t_hd hd)
{
	hd.z = hd.i;
	hd.print = 1;
	hd.count++;
	return (hd);
}

t_hd	check_printable(char **cmdl, t_quote cq, t_hd hd, char ***new_s)
{
	while (cmdl[hd.i][hd.j])
	{
		cq = check_quotes(cq, hd.j, cmdl[hd.i]);
		if (((cq.ind || cq.ins) || strncmp("<<", &cmdl[hd.i][hd.j], 2)))
			hd = numerate(hd);
		if (!cq.ind && !cq.ins && !is_quote(cmdl[hd.i][hd.j]))
		{
			if (cmdl[hd.i][hd.j] == '<' && cmdl[hd.i][hd.j + 1] == '<')
			{
				if (cmdl[hd.i][hd.j + 2])
					hd.j += get_fl(&cmdl[hd.i][hd.j + 2]) + 2;
				else if (cmdl[hd.i + 1])
					hd = set_on_new_s(cmdl, cq, hd, new_s);
				continue ;
			}
		}
		if (cmdl[hd.i][hd.j])
			hd.j++;
	}
	return (hd);
}

int	wc_heredoc(char **cmdl)
{
	t_hd	hd;
	t_quote	cq;

	ft_memset(&hd, 0, sizeof(t_hd));
	while (cmdl[hd.i])
	{
			hd.j = 0;
		ft_memset(&cq, 0, sizeof(t_quote));
		while (cmdl[hd.i][hd.j])
		{
			cq = check_quotes(cq, hd. j, cmdl[hd.i]);
			hd = check_dprintable(cmdl, cq, hd);
		}
		if (hd.print)
		{
			hd.wc++;
			hd.print = 0;
		}
		hd.i++;
	}
	return (hd.wc);
}

char	*fill_ns_hd(char *cmdl, int count, t_quote cq, t_hd hd)
{
	char	*new_s;
	int		j;
	int		z;

	j = 0;
	z = 0;
	new_s = (char *)ft_calloc((count + 1), sizeof(char));
	if (!new_s)
		return (NULL);
	while (j < count && cmdl[z])
	{
		cq = check_quotes(cq, z, cmdl);
		if ((!cq.ind && !cq.ins) && !strncmp("<<", &cmdl[z], 2))
			if (cmdl[j + 2])
				z += get_fl(&cmdl[z + 2]) + 2;
		if (hd.contin && hd.z == hd.indx)
		{
				z = hd.contin;
				hd.contin = 0;
		}
		new_s[j++] = cmdl[z];
		if (cmdl[z])
			z++;
	}
	return (new_s);
}

char	**ns_heredoc(char **cmdl, int wc)
{
	char	**new_s;
	t_hd	hd;
	t_quote	cq;

	ft_memset(&hd, 0, sizeof(t_hd));
	new_s = (char **)ft_calloc((wc + 1), sizeof(char *));
	while (cmdl[hd.i])
	{
		hd.j = 0;
		ft_memset(&cq, 0, sizeof(t_quote));
		hd = check_printable(cmdl, cq, hd, &new_s);
		if (hd.print)
		{
			new_s[hd.k++] = fill_ns_hd(cmdl[hd.z], hd.count, cq, hd);
			hd.print = 0;
			hd.count = 0;
		}
		hd.i++;
	}
	return (new_s);
}
