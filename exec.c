/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:34:37 by azarda            #+#    #+#             */
/*   Updated: 2023/06/09 17:04:11 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"


void ft_hairdoc(char **tab)
{
	char *str;
	while(1)
	{
		str = readline("> ");
		if(!ft_strcmp(str, tab[1]))
			break;
		free(str);
		str = NULL;

	}
}
int ft_exucve(char *cmd, char **arg, char **env)
{
	int pid;
		{
			pid = fork();
			if(!pid)
			{
				if(execve(cmd, arg, env) < 0)
				{
				ft_putstr_fd("Minishell: \n ", 2);
				exit (0);
				return (1);
				}
			// ft_free_(env);
			}
		}
	wait(&pid);
	return 0;

}


// void le ()
// {
// 	system("leaks Minishell");
// }
//________________________________________________________________________________

int ft_lstsize(t_env *env)
{
	int i = 0;

	while(env)
	{
		i++;
		env = env->next;
	}
	return i;

}

char **ft_my_env(t_env *en)
{
	char **tab;
	t_env *env = duplicate_linked_list(en);

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

	while(env)
	{
		key = ft_strjoin(ft_strdup(env->key), ft_strdup("="));
		valu = ft_strjoin(key ,ft_strdup(env->valu));
		tab[i] = valu;
		free(valu);
		free(env);
		env = env->next;
		i++;
	}
	free(env);
	// ft_lstclear(&env);
	tab[i] = NULL;
	return tab;
}



//________________________________________________________________________________


void ft_exec(char **tab, t_env *env)
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

	// ft_free_(my_env);


	if(tab[0] != NULL)
	{

		if(!ft_strcmp(tab[0], "<<"))
				ft_hairdoc(tab);
			else
			{
		while(env)
		{
			// puts("-=--=-=--=-=-=--=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-");
			if((!ft_strcmp("PATH", env->key)))
			{

				tmp = ft_split(env->valu, ':');
				break;
			}
			env = env->next;
		}







		// while(env[i])
		// {
		// 	if(!strncmp(env[i],"PATH=", 5))
		// 	{
		// 		str0 = ft_split(env[i], '=');
		// 		tmp = ft_split(str0[1], ':');
		// 		ft_free_(str0);
		// 	}
		// 	i++;
		// }
		i = 0;

		// int fd = open ("test", O_RDWR, 0777);











		if(!(access(tab[0], F_OK)))
		{
			ss = ft_strdup(tab[0]);
		}
		else if(tmp)
		{
		while(tmp[i])
		{
			test = ft_strjoin(ft_strdup("/"), ft_strdup(tab[0]));
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
				printf("Minishell: %s: command not found\n", tab[0]);
		}
		ft_free_(tmp);
		}
		// dup2(fd, 1);
		// printf("--->>%s\n", ss);
//---------------------------------------------------------------------------------------------------
		if(ss)
		{
			ft_exucve(ss, tab, my_env);
		}

		// ft_free_(my_env);

		free(ss);
		ss = NULL;
		}
	}

}
