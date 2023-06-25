/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:34:37 by azarda            #+#    #+#             */
/*   Updated: 2023/06/25 16:24:05 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"



void ft_exucve(char *cmd, char **arg, char **env)
{
	// signal(SIGINT, SIG_DFL);
	// signal(SIGQUIT, SIG_DFL);
	if(execve(cmd, arg, env) < 0)
	{
		free(cmd);
		ft_free_(arg);
		ft_free_(env);
		perror("minishell   exeve faill   :"); // change msg err
		exit (errno);
	}

}



//________________________________________________________________________________

// int ft_extract_status_execve(int stat)
// {
// 	// printf("--> %d\n", stat);
// 	return (0);
// }



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



//________________________________________________________________________________


void ft_exec(char **cmd, t_env *env)
{
	char *test = NULL;
	char **tmp = NULL;
	// char **str0;
	char *ss;
	// int p;
	int i = 0;


	ss = NULL;

	char **my_env = NULL;


	my_env = ft_my_env(env);

		signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	
	if(cmd[0] != NULL)
	{


		while(env)
		{
			if((!ft_strcmp("PATH", env->key)))
			{

				tmp = ft_split(env->valu, ':');
				break;
			}
			env = env->next;
		}
		if(!env)
			ss = ft_strdup(cmd[0]);
		if(cmd[0][0] == '.' || cmd[0][0] == '/')
		{
			free(ss);
			ss = ft_strdup(cmd[0]);
			if(cmd[0][0] == '/' && access(ss, F_OK) == -1)
			{
				perror("minishell : ");
				exit(127);
			}
			if(cmd[0][0] == '.' && access(ss, X_OK) == -1)
			{

				perror("minishell : ");
				exit(126);
			}
			if(tmp)
				ft_free_(tmp);
			}
		else if(tmp)
		{
		while(tmp[i])
		{
			test = ft_strjoin(ft_strdup("/"), ft_strdup(cmd[0]));
			ss = ft_strjoin(ft_strdup(tmp[i]), test);
			if(!(access(ss, F_OK)))
				break;
			else
			{
				free(ss);
				ss = NULL;
				i++;
			}
			if(!tmp[i])
			{

				ft_print_err(cmd[0], ": combjmand not found\n");
				exit(127);
				return ;
			}
		}
		ft_free_(tmp);
		}


//---------------------------------------------------------------------------------------------------
		// int pid = 0;
		// int status;

		if(ss)
		{
			ft_exucve(ss, cmd, my_env);
		}
		// waitpid(pid, &status, 0);

		// while (wait(NULL) != -1)
		// 	;
		// ex_s = ft_extract_status_execve(status);

		ft_free_(my_env);

		free(ss);
		ss = NULL;
		}
}
