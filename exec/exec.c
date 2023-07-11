/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:34:37 by azarda            #+#    #+#             */
/*   Updated: 2023/07/11 04:34:21 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"



void ft_exucve(char *cmd, char **arg, char **env)
{
	// int i = 0;
	// while(arg[i])
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
		if(env->valu)
		{
		key = ft_strjoin(ft_strdup(tmp->key), ft_strdup("="));
		valu = ft_strjoin(key ,ft_strdup(tmp->valu));
		tab[i] = valu;
		}
		env = tmp->next;
		i++;
		free(tmp);
	}
	ft_lstclear(&env);
	return (tab[i] = NULL, tab);
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
				ft_putstr_fd("minishell: ", 2);
				perror(ss);
				exit(126);
			}
			return (ss);
		}
	return (NULL);
}


char *is_valid_cmd(char **path, char *cmd)
{
	int i = 0;
	char *test;
	char *ss;
	while(path[i])
	{
		// printf("-->%s\n", cmd);
		if(!cmd[0])
			return (ft_print_err(cmd, ": command not found\n"), exit(127), NULL);
		test = ft_strjoin(ft_strdup("/"), ft_strdup(cmd));
		ss = ft_strjoin(ft_strdup(path[i]), test);
		if(!(access(ss, F_OK)))
			return (ss);
		else
		{
			free(ss);
			ss = NULL;
			i++;
		}
		if(!path[i])
			return (ft_print_err(cmd, ": command not found\n"), exit(127), NULL);
	}
	ft_free_(path);
	return (NULL); // ai3adat nadar
}

//________________________________________________________________________________
char *ft_prepar_path(char *cmd)
{

	char **path;
	char *ss;
	ss = NULL;
		path = ft_get_path(g_v.env);
		if(!path) // if path unsett
			ss = ft_strdup(cmd);
		if(is_path_exec(cmd))
		{
			if(path)
				ft_free_(path);
			return(is_path_exec(cmd));
		}
		else if(path)
		{


			return (is_valid_cmd(path, cmd));
		}
	return (ss);
}

void ft_exec(char **cmd, t_env *env)
{
	char *ss;
	ss = NULL;
	char **my_env = NULL;

	if (!cmd)
		exit(0);
	my_env = ft_my_env(env);


	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if(cmd[0] != NULL)
	{
		ss = ft_prepar_path(cmd[0]);
		if(ss)
			ft_exucve(ss, cmd, my_env);
		free(ss);
		ss = NULL;
	}
	ft_free_(my_env);
}
