/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 23:11:47 by azarda            #+#    #+#             */
/*   Updated: 2023/07/18 06:30:55 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

char	*ft_new_key(char *cmd)
{
	int		i;
	char	*new_key;

	i = 0;
	new_key = NULL;
	if (cmd)
	{
		if (ft_signe(cmd, '='))
		{
			i = ft_signe(cmd, '=');
			if (cmd[i - 1] == '+')
				i -= 1;
			new_key = ft_substr(cmd, 0, i);
			return (new_key);
		}
	}
	return (ft_strdup(cmd));
}

int	ft_autre_cara(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '=' && cmd[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	ft_invalid_unset_export(char *cmd, char *bult, int i)
{
	if (cmd && !ft_isalpha(cmd[0]) && cmd[0] != '_')
	{
		if (cmd[0] == '-')
			return (g_v.ex_s = 2, ft_print_err(bult, \
			" : Does not take options\n"), 1);
		else
			ft_print_err(cmd, " : not a valid identifier\n");
		g_v.ex_s = 1;
		return (1);
	}
	if (cmd && !i)
	{
		if (ft_autre_cara(cmd))
		{
			ft_print_err(cmd, " : not a valid identifier\n");
			return (g_v.ex_s = 1, 1);
		}
	}
	if (!ft_strcmp(bult, "unset") && (ft_autre_cara(cmd) || ft_signe(cmd, '=')))
	{
		ft_print_err(cmd, " : not a valid identifier\n");
		return (g_v.ex_s = 1, 1);
	}
	return (0);
}

int	ft_invalid_export_unset(char *cmd, char *bult)
{
	char	*new;
	int		i;

	i = ft_signe(cmd, '=');
	if (ft_invalid_unset_export(cmd, bult, i))
		return (1);
	new = ft_new_key(cmd);
	if (cmd && ft_autre_cara(new))
	{
		ft_print_err(cmd, " : not a valid identifier\n");
		return (g_v.ex_s = 1, free(new), 1);
	}
	free(new);
	if (i)
	i -= 1;
	if (cmd && (cmd[i] != '+' && cmd[i] != '_' && !ft_isalnum(cmd[i])))
	{
		ft_print_err(cmd, " : not a valid identifier\n");
		return (g_v.ex_s = 1, 1);
	}
	return (0);
}

int	ft_check_old_env(char *cmd)
{
	int		i;
	char	*new_key;
	t_env	*tmp;

	i = 0;
	tmp = g_v.env;
	new_key = ft_new_key(cmd);
	i = ft_signe(cmd, '=');
	while (cmd && tmp)
	{
		if (!ft_strcmp(new_key, tmp->key))
		{
			if (i && cmd[i - 1] == '+')
				tmp->valu = ft_strjoin(tmp->valu, ft_substr(cmd, i + 1, \
				(ft_strlen(cmd) - i)));
			else if (i)
			{
				free(tmp->valu);
				tmp->valu = ft_substr(cmd, i + 1, (ft_strlen(cmd) - i));
			}
			return (free(new_key), 1);
		}
		tmp = tmp->next;
	}
	return (free(new_key), 0);
}
