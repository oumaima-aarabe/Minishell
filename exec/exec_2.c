/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 06:07:39 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/18 07:49:24 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

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

void	ft_execut_cd(char *str, t_env *env)
{
	char	*old;
	char	*hom;

	old = NULL;
	hom = NULL;
	while (env)
	{
		if (!ft_strcmp("HOME", env->key))
			hom = env->valu;
		if (!ft_strcmp("PWD", env->key))
			old = ft_strdup(env->valu);
		env = env->next;
	}
	if (!old)
		old = getcwd(NULL, 0);
	if (ft_cd_execut(str, hom, old))
		return ;
	if (ft_check_getcwd())
	{
		free(old);
		return ;
	}
	ft_change_env(g_v.env, old);
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
