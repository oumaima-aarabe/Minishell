/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:49:15 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/18 14:24:53 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	ft_signe(char *st, char c)
{
	int	i;

	i = 0;
	while (st[i])
	{
		if (st[i] == c)
			return (i);
		i++;
	}
	return (0);
}

void	ft_shelvl(t_env *env)
{
	t_env		*tmp;
	static int	i;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp("SHLVL", tmp->key))
		{
			i = ft_atoi(tmp->valu);
			if (i >= 999)
				i = 0;
			else
				i += 1;
			free(tmp->valu);
			tmp->valu = ft_itoa(i);
			return ;
		}
		tmp = tmp->next;
	}
	ft_add_export("SHLVL=1");
}

void	environment(char **env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i])
	{
		j = ft_signe(env[i], '=');
		ft_lstadd_back(&g_v.env, ft_creat(ft_substr(env[i], 0, j), \
		ft_substr(env[i], j + 1, (ft_strlen(env[i]) - j))));
		i++;
	}
	ft_shelvl(g_v.env);
}

char	*ft_take_key(char *str, t_env *env, int j, int len)
{
	char	*tmp;

	tmp = ft_strndup(str + j, len);
	while (env)
	{
		if (!ft_strncmp(tmp, env->key, len + 1))
		{
			if (env->valu)
				return (free(tmp), ft_strdup(env->valu));
			else
				break ;
		}
		env = env->next;
	}
	return (free(tmp), ft_strdup(""));
}

void	ft_execut_env(t_env *env, char **cmd)
{
	if (cmd[1])
	{
		if (cmd[1][0] == '-')
			ft_print_err(cmd[0], ": Does not take options\n");
		else
			ft_print_err(cmd[0], ": Does not take arguments\n");
		g_v.ex_s = 1;
		return ;
	}
	while (env)
	{
		if (env->valu)
			printf("%s=%s\n", env->key, env->valu);
		env = env->next;
	}
}
