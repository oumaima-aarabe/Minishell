/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 01:39:03 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/17 13:28:57 by azarda           ###   ########.fr       */
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
	if (ft_strlen(ex.value))
	{
		int k = ft_strlen(ex.value);
		ex.expanded = ft_strjoin(ex.value, ex.new);
		free(cmd);
		cmd = ft_strjoin(ex.tmp, ex.expanded);
		*j += k;
	}
	else
	{

		free(ex.value);
		free(cmd);
		cmd = ft_strjoin(ex.tmp, ex.new);
	}
	return (cmd);
}

char	*ft_expand(char *cmd, t_env *en)
{
	int		j;
	t_quote	check_q;

	j = 0;
	check_q = init_q();
	if (cmd)
	{
		while (cmd[j])
		{
			check_q = check_quotes(check_q, j, cmd);
			if (!check_q.ins && (cmd[j] == '$' && cmd[j + 1] == '?'))
				cmd = expandinterog(cmd, j);
			else if (!check_q.ins && cmd[j] == '$' && \
			cmd[j + 1] && (ft_isalpha(cmd[j + 1]) || cmd[j + 1] == '_'))
				cmd = expanding(cmd, &j, en);
			else if (cmd[j])
				j++;
		}
	}
	return (cmd);
}
