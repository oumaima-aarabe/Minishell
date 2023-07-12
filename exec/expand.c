/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 01:39:03 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/12 03:33:12 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

t_quote	init_q(void)
{
	t_quote	check_q;

	check_q.in_dquotes = 0;
	check_q.in_squotes = 0;
	return (check_q);
}

t_quote	check_quotes(t_quote check_q, int j, char *cmd)
{
	if (cmd[j] == '\'')
	{
		if (!check_q.in_dquotes)
			check_q.in_squotes = !check_q.in_squotes;
	}
	else if (cmd[j] == '\"')
	{
		if (!check_q.in_squotes)
			check_q.in_dquotes = !check_q.in_dquotes;
	}
	return (check_q);
}

char	*expandinterog(char *cmd, int j)
{
	t_exv	usd_v;

	usd_v.tmp = ft_substr(cmd, 0, j);
	usd_v.new = ft_substr(cmd, j + 2, ft_strlen(cmd) - j);
	free(cmd);
	cmd = ft_strjoin(usd_v.tmp, ft_strjoin(ft_itoa(g_v.ex_s), usd_v.new));
	g_v.ex_s = 0;
	return (cmd);
}

char	*expanding(char *cmd, int *j, t_env *en)
{
	t_exv	usd_v;

	usd_v.pos = *j + 1;
	usd_v.len = 0;
	while (cmd[usd_v.pos] && (isalnum(cmd[usd_v.pos]) || cmd[usd_v.pos] == '_'))
		usd_v.pos++;
	usd_v.len = usd_v.pos - (*j + 1);
	usd_v.tmp = ft_substr(cmd, 0, *j);
	usd_v.new = ft_substr(cmd, *j + usd_v.len + 1, \
	ft_strlen(cmd) - (*j + usd_v.len + 1));
	usd_v.value = ft_take_key(cmd, en, *j + 1, usd_v.len);
	if (ft_strlen(usd_v.value))
	{
		usd_v.expanded = ft_strjoin(usd_v.value, usd_v.new);
		free(cmd);
		cmd = ft_strjoin(usd_v.tmp, usd_v.expanded);
		*j += usd_v.len;
	}
	else
	{
		free(cmd);
		cmd = ft_strjoin(usd_v.tmp, usd_v.new);
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
			if (!check_q.in_squotes && (cmd[j] == '$' && cmd[j + 1] == '?'))
				cmd = expandinterog(cmd, j);
			else if (!check_q.in_squotes && cmd[j] == '$' && \
			cmd[j + 1] && (isalpha(cmd[j + 1]) || cmd[j + 1] == '_'))
				cmd = expanding(cmd, &j, en);
			else if (cmd[j])
				j++;
		}
	}
	return (cmd);
}
