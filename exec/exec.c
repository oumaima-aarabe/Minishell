/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:34:37 by azarda            #+#    #+#             */
/*   Updated: 2023/06/26 01:13:31 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"



void ft_exucve(char *cmd, char **arg, char **env)
{
	if(execve(cmd, arg, env) < 0)
	{
		free(cmd);
		ft_free_(arg);
		ft_free_(env);
		perror("minishell   exeve faill   :"); // change msg err
		exit (errno);
	}
}









char **ft_my_env(t_env *en)
{
	char **tab;
	t_env *env = duplicate_linked_list(en);
	t_env *tmp;

	tab = (char **)malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	int i = 0;
	char *key;
	char *valu;
	tmp = NULL;

	while(env)
	{
		tmp = env;
		key = ft_strjoin(ft_strdup(tmp->key), ft_strdup("="));
		valu = ft_strjoin(key ,ft_strdup(tmp->valu));
		tab[i] = valu;
		env = tmp->next;
		i++;
		free(tmp);
	}
	ft_lstclear(&env);
	tab[i] = NULL;
	return tab;
}

char **ft_get_path(t_env *env)
{
	char **path;
	path = NULL;
	while(env)
	{
		if((!ft_strcmp("PATH", env->key)))
		{
			path = ft_split(env->valu, ':');
			return (path);
		}
		env = env->next;
	}
	return (path);
}

int ft_is_path(char *str)
{
	int i = 0 ;
	while(str[i])
	{
		if(str[i] == '/')
			return(1);
		i++;
	}
	return (0);
}

char *is_path_exec(char *cmd)
{
	char *ss = NULL;
		if(ft_is_path(cmd) ||  (cmd[0] == '.' && cmd[1] == '/'))
		{
			ss = ft_strdup(cmd);
			if(ft_is_path(cmd) && access(ss, F_OK) == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				perror(ss);
				exit(127);
			}
			if((cmd[0] == '.' && cmd[1] == '/') && access(ss, X_OK) == -1)
			{
				ft_putstr_fd("minishell: zab hada ", 2);
				perror(ss);
				exit(126);
			}
			return (ss);
		}
	return (NULL);
}

//________________________________________________________________________________


void ft_exec(char **cmd, t_env *env)
{
	char *test = NULL;
	char **path = NULL;
	char *ss;
	int i = 0;

	ss = NULL;

	char **my_env = NULL;


	my_env = ft_my_env(env);

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);

	if(cmd[0] != NULL)
	{
		path = ft_get_path(g_v.env);
		if(!path) // if path unsett
			ss = ft_strdup(cmd[0]);

		printf(" -- == -- >> %s\n", is_path_exec(cmd[0]));
		if(is_path_exec(cmd[0]))
		{
			ss = is_path_exec(cmd[0]);
			if(path)
				ft_free_(path);
		}
		else if(path)
		{
		while(path[i])
		{
			test = ft_strjoin(ft_strdup("/"), ft_strdup(cmd[0]));
			ss = ft_strjoin(ft_strdup(path[i]), test);
			if(!(access(ss, F_OK)))
				break;
			else
			{
				free(ss);
				ss = NULL;
				i++;
			}
			if(!path[i])
			{

				ft_print_err(cmd[0], ": command not found\n");
				exit(127);
				return ;
			}
		}
		ft_free_(path);
		}
//---------------------------------------------------------------------------------------------------
		if(ss)
			ft_exucve(ss, cmd, my_env);
		ft_free_(my_env);
		free(ss);
		ss = NULL;
		}
}
