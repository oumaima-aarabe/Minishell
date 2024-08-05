/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 06:29:18 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/18 06:30:43 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	ft_check_expor(char *cmd)
{
	if (ft_invalid_export_unset(cmd, "export"))
		return (1);
	if (ft_check_old_env(cmd))
		return (1);
	return (0);
}

int	ft_add_export(char *cmd)
{
	int	j;

	j = 0;
	if (ft_signe(cmd, '='))
	{
		j = ft_signe(cmd, '=');
		if (cmd[j - 1] == '+')
			ft_lstadd_back(&g_v.env, ft_creat(ft_substr(cmd, 0, j - 1), \
			ft_substr(cmd, j + 1, ft_strlen(cmd) - j)));
		else
			ft_lstadd_back(&g_v.env, ft_creat(ft_substr(cmd, 0, j), \
			ft_substr(cmd, j + 1, ft_strlen(cmd) - j)));
	}
	else
		ft_lstadd_back(&g_v.env, ft_creat(ft_strdup(cmd), NULL));
	return (1);
}

int	ft_check_add_export(char **cmd, int i)
{
	while (cmd[i])
	{
		if (ft_check_expor(cmd[i]))
		{
			if (cmd[i + 1])
			{
				i++;
				continue ;
			}
			return (1);
		}
		if (ft_add_export(cmd[i]))
		{
			if (cmd[i + 1])
			{
				i++;
				continue ;
			}
			return (1);
		}
		i++;
	}
	return (0);
}

t_env	*ft_sort_export(t_env *tmp)
{
	t_env	*tmp1;
	char	*swap;

	tmp1 = tmp;
	while (tmp && tmp->next != NULL)
	{
		if ((compar(tmp->key[0], tmp->next->key[0])) == 0)
		{
			swap = tmp->key;
			tmp->key = tmp->next->key;
			tmp->next->key = swap;
			swap = tmp->valu;
			tmp->valu = tmp->next->valu;
			tmp->next->valu = swap;
			tmp = tmp1;
		}
		else
			tmp = tmp->next;
	}
	tmp = tmp1;
	return (tmp);
}
