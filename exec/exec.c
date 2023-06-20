/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:34:37 by azarda            #+#    #+#             */
/*   Updated: 2023/06/20 22:09:05 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"



void ft_exucve(char *cmd, char **arg, char **env)
{
	int pid;
			pid = fork();
			if(!pid)
			{
				if(execve(cmd, arg, env) < 0)
				{
				ft_print_err(cmd , " : No such file or directory\n");
				free(cmd);
				ft_free_(arg);
				ft_free_(env);
				exit (0);
				}
			// ft_free_(env);
			}
	wait(&pid);

}


// void le ()
// {
// 	system("leaks minishell");
// }
//________________________________________________________________________________



char **ft_my_env(t_env *en)
{
	char **tab;
	t_env *env = duplicate_linked_list(en);
	t_env *tmp;

	// while(env)
	// {
	// 	printf("key is  %s valu is %s\n" ,env->key, env->valu);
	// 	env = env->next;
	// }
	// exit(8);



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


void ft_exec(splitnode *ptr, t_env *env)
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



	if(ptr->splitdata[0] != NULL)
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
			ss = ft_strdup(ptr->splitdata[0]);
		if(ptr->splitdata[0][0] == '.' || ptr->splitdata[0][0] == '/')
		{
			free(ss);
			if(tmp)
				ft_free_(tmp);
			ss = ft_strdup(ptr->splitdata[0]);
		}
		else if(tmp)
		{
		while(tmp[i])
		{
			test = ft_strjoin(ft_strdup("/"), ft_strdup(ptr->splitdata[0]));
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
				ft_print_err(ptr->splitdata[0], ": command not found\n");
				ex_s = 127;
			}
		}
		ft_free_(tmp);
		}


//---------------------------------------------------------------------------------------------------

		if(ss)
		{
			ft_exucve(ss, ptr->splitdata, my_env);
		}

		ft_free_(my_env);

		free(ss);
		ss = NULL;
		}
}
