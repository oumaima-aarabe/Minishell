/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:34:37 by azarda            #+#    #+#             */
/*   Updated: 2023/07/18 05:12:20 by azarda           ###   ########.fr       */
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
		if(ft_get_path(g_v.env) == NULL)
			exit (127);
		exit (errno);
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
	return (NULL);
}

char	*is_valid_cmd(char **path, char *cmd)
{
	int		i;
	char	*test;
	char	*ss;

	i = 0;
	while (path[i])
	{
		if (!cmd[0] || (cmd[0] == '.' || (cmd[0] == '.' && cmd[1] == '.')))
			return (ft_print_err(cmd, ": command not found\n"), exit(127), NULL);
		test = ft_strjoin(ft_strdup("/"), ft_strdup(cmd));
		ss = ft_strjoin(ft_strdup(path[i]), test);
		if (!(access(ss, F_OK)))
			return (ss);
		else
		{
			free(ss);
			ss = NULL;
			i++;
		}
		if (!path[i])
			return (ft_print_err(cmd, ": command not found\n"), exit(127), NULL);
	}
	ft_free_(path);
	return (NULL);
}

char	*ft_prepar_path(char *cmd)
{
	char	**path;
	char	*ss;

	ss = NULL;
	path = ft_get_path(g_v.env);
	if (!path)
		ss = ft_strdup(cmd);
	if (is_path_exec(cmd))
	{
		if (path)
			ft_free_(path);
		return (is_path_exec(cmd));
	}
	else if (path)
	{
		return (is_valid_cmd(path, cmd));
	}
	return (ss);
}

void	ft_exec(char **cmd, t_env *env)
{
	char	*ss;
	char	**my_env;
	t_env	*en_new;

	ss = NULL;
	if (!cmd)
		exit(0);
	en_new = duplicate_linked_list(env);
	my_env = ft_my_env(en_new, 0);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (cmd[0] != NULL)
	{
		ss = ft_prepar_path(cmd[0]);
		if (ss)
			ft_exucve(ss, cmd, my_env);
		free(ss);
		ss = NULL;
	}
	ft_free_(my_env);
}
