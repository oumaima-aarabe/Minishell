/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:34:37 by azarda            #+#    #+#             */
/*   Updated: 2023/07/19 01:18:55 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

char	**ft_get_path(t_env *env)
{
	char	**path;

	path = NULL;
	while (env)
	{
		if ((!ft_strcmp("PATH", env->key)))
		{
			path = ft_split(env->valu, ':');
			return (path);
		}
		env = env->next;
	}
	return (path);
}



void	ft_exucve(char *cmd, char **arg, char **env)
{
	if (execve(cmd, arg, env) < 0)
	{
		ft_free_(arg);
		ft_free_(env);
		ft_putstr_fd("Minishell ", 2);
		perror(cmd);
		free(cmd);
		if (errno == 2)
			exit(127);
		else if (errno == 130)
			exit(1);
		else if (errno == 13 || errno == 20)
			exit(126);
		exit(errno);
	}
}

char	**ft_my_env(t_env *env, int i)
{
	char	**tab;
	t_env	*tmp;
	char	*key;
	char	*valu;

	tab = (char **)malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	if (!tab)
		return (NULL);
	tmp = NULL;
	while (env)
	{
		tmp = env;
		if (env->valu != NULL)
		{
		key = ft_strjoin(ft_strdup(tmp->key), ft_strdup("="));
		valu = ft_strjoin(key, ft_strdup(tmp->valu));
		tab[i] = valu;
		i++;
		}
		env = tmp->next;
		free(tmp);
	}
	ft_lstclear(&env);
	return (tab[i] = NULL, tab);
}

int	ft_is_path(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char	*is_path_exec(char *cmd)
{
	char	*ss;
	DIR		*dir;

	ss = ft_strdup(cmd);
	if (ft_is_path(cmd) || (cmd[0] == '.' && cmd[1] == '/'))
	{
		if (access(ss, F_OK) == -1)
		{
			ft_putstr_fd("Minishell ", 2);
			return (perror(ss), exit(127), NULL);
		}
		if (access(ss, X_OK) == -1)
		{
			ft_putstr_fd("Minishell ", 2);
			return (perror(ss), exit(126), NULL);
		}
		dir = opendir(ss);
		if (dir != NULL)
		{
			ft_print_err(cmd, ": is a directory\n");
			return (closedir(dir), exit(126), NULL);
		}
		return (ss);
	}
	return (free(ss), NULL);
}
