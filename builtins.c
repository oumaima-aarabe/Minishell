/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 16:32:26 by azarda            #+#    #+#             */
/*   Updated: 2023/06/09 18:16:18 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

//________________________________echo____________________________________________

void ft_execut_echo(char **tab)
{
	int i = 0;
	int j = 0;
	int bol = 1;

	if(!ft_strcmp(tab[i], "echo"))
	{
		i++;
		while(tab[i] && (ft_strncmp(tab[i], "-n", 2)) == 0)
		{
			j = 2;
			while(tab[i][j] && tab[i][j] == 'n')
				j++;
			if(tab[i][j] && tab[i][j] != 'n')
				break;
			if(tab[i][j])
				bol = 1;
			else
				bol = 0;
			i++;
		}
		while (tab[i])
		{
			printf("%s", tab[i]);
			i++;
			if(tab[i] != NULL)
				printf(" ");
		}
		if(bol)
			printf("\n");
	}
}

void ft_execut_cd(char **str, t_env *env)
{
	t_env *tmp = env;


	while(env)
	{
		if(!ft_strcmp("HOME", env->key))
		break;
		env = env->next;
	}
	if(!ft_strcmp(str[0], "cd"))
	{
		if(!str[1])
			chdir(env->valu);
		else if(chdir(str[1]) < 0)
		{
			ft_putstr_fd("Minishell: cd: ", 2);
			perror(str[1]);
		}
	}
	while(tmp)
	{
		if(!ft_strcmp("PWD", tmp->key))
		{
			free(tmp->valu);
			tmp->valu = getcwd(NULL, 0);
		}
		tmp = tmp->next;
	}
}


//__________________________________unset_________________________________________



//________________________________________________________________________________


//++++++++++++++++++++++++++++++++++++export++++++++++++++++++++++++++++++++++++++


int compar(int a, int b)
{
	if(a > b)
		return (0);
	return(1);
}

int ft_egal(char *st)
{
	int i = 0;

	while(st[i])
	{
		if(st[i] == '=')
		return (i);
		i++;
	}
	return 0;
}

void ft_execut_export(t_env *env, char **cmd)
{
	char 	*swap;

	t_env *tmp;
	t_env *tmp1;
	int i;

	if(cmd[1])
	{
		if(ft_egal(cmd[1]))
		{
			i = ft_egal(cmd[1]);
			ft_lstadd_back(&env,ft_creat(ft_substr(cmd[1], 0, i), ft_substr(cmd[1], i + 1, ft_strlen(cmd[1]) - i)));
		}
		else
			ft_lstadd_back(&env, ft_creat(ft_strdup(cmd[1]), NULL));
		return ;
	}
	tmp = duplicate_linked_list(env);

	tmp1 = tmp;
	while(tmp->next != NULL)
	{
		if ((compar(tmp->key[0], tmp->next->key[0])) == 0)
		{
			swap = tmp->key;
			tmp->key = tmp->next->key;
			tmp->next->key = swap;
			swap = tmp->valu;
			tmp->valu = tmp->next->valu;
			tmp->next->valu = swap;
			tmp = tmp1;
		}
		else
			tmp = tmp->next;
	}
	tmp = tmp1;
	while(tmp)
	{
		if(tmp->valu)
		printf("declare -x %s=\"%s\"\n",tmp->key, tmp->valu);
		else
		printf("declare -x %s\n",tmp->key);
		tmp = tmp->next;
	}
	ft_lstclear(&tmp1);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// void ft_execut_unset(t_env *env, char **cmd)
// {
// 	deleteNode(&env, cmd[1]);
// }

void ft_execut_env(t_env *env)
{
	while(env )
	{
		if(env->valu)
		printf("%s=%s\n", env->key, env->valu);
		env = env->next;
	}
}

//___________________________________exit_________________________________________



//________________________________________________________________________________

int ft_execut_bultins(char **cmd, t_env *env)
{
	if(!ft_strcmp(cmd[0], "echo"))
	{
		ft_execut_echo(cmd);
		return (1);
	}

	else if(!ft_strcmp(cmd[0], "cd"))
	{
		ft_execut_cd(cmd, env);
		return (1);
	}

	else if(!ft_strcmp(cmd[0], "pwd"))
	{
		printf("%s\n", getcwd(NULL, 0));
		return (1);
	}

	else if(!(ft_strcmp(cmd[0], "export")))
	{
		ft_execut_export(env, cmd);
		return (1);
	}

	// else if(!(ft_strcmp(cmd[0], "unset")))
	// {
	// 		ft_execut_unset(env, cmd);
		// return (1);
	// }

	else if(!(ft_strcmp(cmd[0], "env")))
	{
			ft_execut_env(env); // he nide SHELV
			return(1);
	}

	else if(!ft_strcmp(cmd[0], "exit"))
		{
			// free(pwd);
			// atexit(lea);
			printf("exit\n");
			exit(0);
		}
	return(0);
}
