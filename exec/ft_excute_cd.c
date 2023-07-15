/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_excute_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:15:12 by azarda            #+#    #+#             */
/*   Updated: 2023/07/15 01:39:09 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void ft_change_env(t_env *env, char *old)
{
	// t_env  *env = en;
	while(env)
	{
		if(!ft_strcmp("PWD", env->key))
		{
			free(env->valu);
			env->valu = getcwd(NULL, 0);
		}
		if(!ft_strcmp("OLDPWD", env->key))
		{
			free(env->valu);
			env->valu = old;
		}
		env = env->next;
	}
	// free(old);
}

void ft_cd_home(char *hom)
{
		if(!hom)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			g_v.ex_s = 1;
 		}
		else if(chdir(hom) < 0)
		{
			ft_putstr_fd("minishell: cd: ", 2);
			g_v.ex_s = 1;
			perror(hom);
		}
}

void ft_cd_old_pwd(t_env *env)
{
	while (env)
	{
		if(!ft_strcmp(env->key, "OLDPWD"))
		{
			if(chdir(env->valu) < 0)
			{
				ft_putstr_fd("minishell: cd: ", 2);
				perror(env->valu);
				g_v.ex_s = 1;
				break;
			}
			printf("%s\n",env->valu);
			break;
		}
		env = env->next;
	}
	if(!env)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		g_v.ex_s = 1;
	}

}
int ft_check_getcwd()
{
	char *pwd;
	pwd = getcwd(NULL, 0);
	if(pwd == NULL)
	{
		ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
		free(pwd);
		return(1);
	}
	free(pwd);
	return (0);
}

int ft_cd_execut(char *str, char *hom)
{

	if(!str)
		ft_cd_home(hom);
	else if(str[0] == '-' && str[1] == '\0')
		ft_cd_old_pwd(g_v.env);
	else if(chdir(str) < 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(str);
		g_v.ex_s = 1;
		return 1;
	}
	return (0);
}

void ft_execut_cd(char *str, t_env *env)
{
	char *old;
	char *hom;

	old = NULL;
	hom = NULL;
	while(env)
	{
		if(!ft_strcmp("HOME", env->key))
			hom = env->valu;
		if(!ft_strcmp("PWD", env->key))
			old = ft_strdup(env->valu);
		env = env->next;
	}
	if(!old)
		old = getcwd(NULL, 0);
	if(ft_cd_execut(str, hom))
		return ;
	if(ft_check_getcwd())
	{
		free(old);
		return ;
	}
	// printf("old -> %s |||  adress old -> %p\n", old, old);
	ft_change_env(g_v.env, old);
}
