/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 23:11:47 by azarda            #+#    #+#             */
/*   Updated: 2023/07/17 11:12:06 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	compar(int a, int b)
{
	if (a > b)
		return (0);
	return (1);
}

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
			return (g_v.ex_s = 2, ft_print_err(bult, " : Does not take options\n"), 1);
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

void	ft_execut_export(char **cmd)
{
	t_env	*tmp;
	t_env	*tmp1;

	if (ft_check_add_export(cmd, 1))
		return ;
	tmp = duplicate_linked_list(g_v.env);
	tmp = ft_sort_export(tmp);
	tmp1 = tmp;
	while (tmp)
	{
		if (tmp->valu)
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->valu);
		else
			printf("declare -x %s\n", tmp->key);
		tmp = tmp->next;
	}
	ft_lstclear(&tmp1);
}
