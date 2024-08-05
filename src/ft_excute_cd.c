/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_excute_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:15:12 by azarda            #+#    #+#             */
/*   Updated: 2023/07/18 06:27:48 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	ft_change_env(t_env *env, char *old)
{
	while (env)
	{
		if (!ft_strcmp("PWD", env->key))
		{
			free(env->valu);
			env->valu = getcwd(NULL, 0);
		}
		if (!ft_strcmp("OLDPWD", env->key))
		{
			free(env->valu);
			env->valu = ft_strdup(old);
		}
		env = env->next;
	}
	free(old);
}

int	ft_cd_home(char *hom)
{
	if (!hom)
	{
		ft_putstr_fd("Minishell cd: HOME not set\n", 2);
		g_v.ex_s = 1;
		return (1);
	}
	else if (chdir(hom) < 0)
	{
		ft_putstr_fd("Minishell cd: ", 2);
		g_v.ex_s = 1;
		perror(hom);
		return (1);
	}
	return (0);
}

int	ft_cd_old_pwd(t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(env->key, "OLDPWD"))
		{
			if (chdir(env->valu) < 0)
			{
				ft_putstr_fd("Minishell cd: ", 2);
				perror(env->valu);
				g_v.ex_s = 1;
				return (1);
			}
			printf("%s\n", env->valu);
			return (0);
		}
		env = env->next;
	}
	if (!env)
	{
		ft_putstr_fd("Minishell cd: OLDPWD not set\n", 2);
		g_v.ex_s = 1;
		return (1);
	}
	return (0);
}

int	ft_check_getcwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		ft_putstr_fd("Minishell : cd: error retrieving current directory:", 2);
		ft_putstr_fd(" getcwd: cannot access parent ", 2);
		ft_putstr_fd("directories: No such file or directory\n", 2);
		free(pwd);
		return (1);
	}
	free(pwd);
	return (0);
}

int	ft_cd_execut(char *str, char *hom, char *old)
{
	if (!str)
	{
		if (ft_cd_home(hom))
			return (free(old), 1);
	}
	else if (str[0] == '-' && str[1] == '\0')
	{
		if (ft_cd_old_pwd(g_v.env))
			return (free(old), 1);
	}
	else if (chdir(str) < 0)
	{
		ft_putstr_fd("Minishell cd: ", 2);
		perror(str);
		free(old);
		g_v.ex_s = 1;
		return (1);
	}
	return (0);
}
