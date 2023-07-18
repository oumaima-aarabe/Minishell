/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 01:39:03 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/18 06:24:40 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

char	*expandinterog(char *cmd, int j)
{
	t_exv	usd_v;

	usd_v.tmp = ft_substr(cmd, 0, j);
	usd_v.new = ft_substr(cmd, j + 2, ft_strlen(cmd) - j);
	free(cmd);
	cmd = ft_strjoin(usd_v.tmp, ft_strjoin(ft_itoa(g_v.ex_s), usd_v.new));
	return (cmd);
}

char	*expanding(char *cmd, int *j, t_env *en)
{
	t_exv	ex;

	ex.pos = *j + 1;
	ex.len = 0;
	while (cmd[ex.pos] && (ft_isalnum(cmd[ex.pos]) || cmd[ex.pos] == '_'))
		ex.pos++;
	ex.len = ex.pos - (*j + 1);
	ex.tmp = ft_substr(cmd, 0, *j);
	ex.new = ft_substr(cmd, *j + ex.len + 1, \
	ft_strlen(cmd) - (*j + ex.len + 1));
	ex.value = ft_take_key(cmd, en, *j + 1, ex.len);
	ex.pos = ft_strlen(ex.value);
	if (ex.pos)
	{
		ex.expanded = ft_strjoin(ex.value, ex.new);
		free(cmd);
		cmd = ft_strjoin(ex.tmp, ex.expanded);
	}
	else
	{
		free(ex.value);
		free(cmd);
		cmd = ft_strjoin(ex.tmp, ex.new);
	}
	return (*j += ex.pos, cmd);
}

char	*ft_expand(char *cmd, t_env *en)
{
	t_quote	cq;

	ft_memset(&cq, 0, sizeof(t_quote));
	if (cmd)
	{
		while (cmd[cq.j])
		{
			cq = check_quotes(cq, cq.j, cmd);
			if (!cq.ins && (cmd[cq.j] == '$' && cmd[cq.j + 1] == '?'))
				cmd = expandinterog(cmd, cq.j);
			else if (!cq.ins && cmd[cq.j] == '$' && cmd[cq.j + 1] && \
			(ft_isalpha(cmd[cq.j + 1]) || cmd[cq.j + 1] == '_'))
				cmd = expanding(cmd, &cq.j, en);
			else if (cmd[cq.j])
				cq.j++;
		}
	}
	return (cmd);
}
