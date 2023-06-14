/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 16:32:26 by azarda            #+#    #+#             */
/*   Updated: 2023/06/10 17:20:49 by azarda           ###   ########.fr       */
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
//_____________________________________cd_________________________________________


void ft_execut_cd(char **str, t_env *env)
{

	t_env *tmp = env;
	char *old;
	char *pwd;
	char *hom;

	while(env)
	{
		if(!ft_strcmp("HOME", env->key))
			hom = env->valu;
		if(!ft_strcmp("PWD", env->key))
		{
			old = ft_strdup(env->valu);
		}
		env = env->next;
	}
	if(!ft_strcmp(str[0], "cd"))
	{
		if(!str[1])
			chdir(hom);
		else if(chdir(str[1]) < 0)
		{
			ft_putstr_fd("Minishell: cd: ", 2);
			perror(str[1]);
		}
		pwd = getcwd(NULL, 0);
		if(pwd == NULL)
		{
			ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
			free(pwd);
			free(old);
			return ;
		}
		free(pwd);


	}
	while(tmp)
	{
		if(!ft_strcmp("PWD", tmp->key))
		{
			free(tmp->valu);
			tmp->valu = getcwd(NULL, 0);
		}
		if(!ft_strcmp("OLDPWD", tmp->key))
		{
			free(tmp->valu);
			tmp->valu = old;
		}
		tmp = tmp->next;
	}
}

//____________________________________pwd_________________________________________

void ft_ft_execut_pwd(char *cmd, t_env *env)
{
	char *pwd;

	if(cmd && cmd[0] == '-' && cmd[1])
	{
		// dup2(2, 1);
		printf("Minishell: pwd: %s: invalid option\n", cmd);
		// dup2(1, 2);
		return;
	}
	pwd = getcwd(NULL, 0);
	if(pwd)
	{
		printf("%s\n", pwd);
		free(pwd);
		return ;
	}
	while(env)
	{
		if(!ft_strcmp("PWD", env->key))
		{
			printf("%s\n", env->valu);
			return ;
		}
		env = env->next;
	}

}






//++++++++++++++++++++++++++++++++++++export++++++++++++++++++++++++++++++++++++++


int compar(int a, int b)
{
	if(a > b)
		return (0);
	return(1);
}


int is_alphabet(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (0);
	return (1);
}

int ft_cheak_expor(char *cmd, t_env *tmp)
{
	int i = 0;


	if(cmd && is_alphabet(cmd[0]) && cmd[0] != '_')
	{
		if(cmd[0] == '-')
			printf("Minishell: export: %c%c: invalid option\n",cmd[0], cmd[1]);
		else
			printf("Minishell: export: `%s': not a valid identifier\n", cmd);
		return 1;
	}
	if(cmd)
	{
	if (ft_sine(cmd, '='))
	{
		i = ft_sine(cmd, '=');
		if(cmd[i - 1] == '+')
		i -= 1;
	}
	else
		i = ft_strlen(cmd);
	}
	if(cmd && ft_sine(cmd, '+')  && (cmd[ft_sine(cmd, '+') + 1]  != '='))
	{
		printf("Minishell: export: `%s': not a valid identifier\n", cmd);
		return 1;
	}
	while(cmd && tmp)
	{
		if(!ft_strncmp(cmd, tmp->key, i))
		{
			i = ft_sine(cmd, '=');
			if(i && cmd[i - 1] == '+')
				tmp->valu =  ft_strjoin(tmp->valu, ft_substr(cmd, i + 1, (ft_strlen(cmd) - i)));
			else if (i)
			{
				free(tmp->valu);
				tmp->valu = ft_substr(cmd, i + 1, (ft_strlen(cmd) - i));
			}
			return 1;
		}
		tmp = tmp->next;
	}
	return 0;
}

int ft_add_export(char *cmd , t_env *env)
{
	int j = 0;
		if(ft_sine(cmd, '='))
		{
			j = ft_sine(cmd, '=');
			ft_lstadd_back(&env,ft_creat(ft_substr(cmd, 0, j), ft_substr(cmd, j + 1, ft_strlen(cmd) - j)));
		}
		else
		{
			ft_lstadd_back(&env, ft_creat(ft_strdup(cmd), NULL));
		}
	return (1);
}

void ft_execut_export(t_env *env, char **cmd)
{
	char 	*swap;

	t_env *tmp;
	t_env *tmp1;
	int i;

	i = 1;


	while(cmd[i])
	{

		if(ft_cheak_expor(cmd[i],env))
		{
			if(cmd[i + 1])
			{
				i++;
				continue;
			}
			return ;
		}
		if (ft_add_export(cmd[i] ,env))
		{
		if(cmd[i + 1])
		{
			i++;
			continue;
		}
		return ;
		}
		i++;
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

//__________________________________unset_________________________________________


void	ft_list_remov(t_env **env, char *cmd)
{
	t_env	*tmp_env;
	t_env	*prev;
	(void)cmd;
	tmp_env = *env;
	prev = NULL;
	while (tmp_env)
	{
		if (!ft_strcmp(tmp_env->key, cmd))
		{
			if (!prev)
			{
				*env = tmp_env->next;
				free(tmp_env->key);
				free(tmp_env->valu);
				free(tmp_env);
			}
			else
			{
				prev->next = tmp_env->next;
				free(tmp_env->key);
				free(tmp_env->valu);
				free(tmp_env);
			}
			return ;
		}
		prev = tmp_env;
		tmp_env = tmp_env->next;
	}
}




void ft_execut_unset(t_env *env, char **cmd)
{
	int i = 1;
	while(cmd[i])
	{
		ft_list_remov(&env, cmd[i]);
		i++;
	}

}



//___________________________________env__________________________________________


void ft_execut_env(t_env *env)
{
	while(env)
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
	// char *pwd;

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
		ft_ft_execut_pwd(cmd[1] ,env);
		return (1);
	}

	else if(!(ft_strcmp(cmd[0], "export"))) // tesst ""
	{
		ft_execut_export(env, cmd);
		return (1);
	}

	else if(!(ft_strcmp(cmd[0], "unset")))
	{
			ft_execut_unset(env, cmd);
		return (1);
	}

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
