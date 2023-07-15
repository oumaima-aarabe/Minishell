/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 16:32:26 by azarda            #+#    #+#             */
/*   Updated: 2023/07/15 01:24:28 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"


//________________________________echo____________________________________________

void ft_execut_echo(char **tab, int i, int j, int bol)
{
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
		ft_putstr_fd(tab[i++], 1);
		if(tab[i] != NULL)
		ft_putstr_fd(" ", 1);
	}
	if(bol)
		ft_putstr_fd("\n", 1);

}



//____________________________________pwd_________________________________________

void ft_execut_pwd(char *cmd, t_env *env)
{
	char *pwd;

	if(cmd && cmd[0] == '-' && cmd[1])
	{
		ft_print_err(cmd ,  ": No take option\n");
		g_v.ex_s = 1;
		return;
	}
	pwd = getcwd(NULL, 0);
	if(pwd)
	{
		printf("%s\n", pwd);
		free(pwd);
		return ;
	}
	free(pwd);
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









//__________________________________unset_________________________________________

void ft_free_plus(char *s1, char *s2, void *s3)
{
	free(s1);
	free(s2);
	free(s3);

}

void	ft_list_remov(char *cmd)
{
	t_env	*tmp_env;
	t_env	*prev;

	tmp_env = g_v.env;
	prev = NULL;
	while (tmp_env)
	{
		if (!ft_strcmp(tmp_env->key, cmd))
		{
			if (!prev)
			{
				prev = tmp_env->next;
				g_v.env = prev;
				ft_free_plus(tmp_env->key, tmp_env->valu, tmp_env);
			}
			else
			{
				prev->next = tmp_env->next;
				ft_free_plus(tmp_env->key, tmp_env->valu, tmp_env);
			}
			return ;
		}
		prev = tmp_env;
		tmp_env = tmp_env->next;
	}
}

void ft_execut_unset(char **cmd)
{
	int i = 1;
	while(cmd[i])
	{
		if(ft_invalid_export_unset(cmd[i], "unset"))
		{
			i++;
			continue;
		}
		// if(cmd[i][0] == '_' && cmd[i][1] == '\0')
		// {
		// 	printf("-->> %s\n", cmd[i]);
		// 	i++;
		// 	continue;
		// }
			ft_list_remov(cmd[i]);
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



int	ft_atoi_exit(char *str)
{
	int		s;
	long	d;

	s = 1;
	d = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			s *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{

		d = d * 10 + *str - '0';
			str++;
	}
	if (*str != '\0')
	{
		ft_print_err(str,  " : numeric argument required\n");
		exit(255);
	}
	return ((int)(d * s));
}

int ft_execut_exit(char **cmd)
{
	int nb;

	nb = 0;
	int i = 0;
	printf("exit\n");
	if(cmd[1])
	{
		if(cmd[1][i])
		{
			nb = ft_atoi_exit(cmd[1]);
			if(cmd[1] && cmd[2])
			{
				ft_putstr_fd("minishell: exit: too many arguments\n", 2);
				g_v.ex_s = 1;
				return(1);
			}
		}
		// else if(nb > 255 && nb < 0)
		// {
		// 	nb = 255;
		// 	nb -= 256;
		// }
	}
	printf("%d\n", nb);
	exit(nb);
}

int ft_execut_bultins(char **cmd)
{
	if(cmd)
	{
	if(!ft_strcmp(cmd[0], "echo"))
		return (ft_execut_echo(cmd, 1, 0, 1), 1);
	g_v.ex_s = 0;
	if(!ft_strcmp(cmd[0], "cd"))
		return (ft_execut_cd(cmd[1], g_v.env),  1);

	else if(!ft_strcmp(cmd[0], "pwd"))
		return (ft_execut_pwd(cmd[1] ,g_v.env), 1);

	else if(!(ft_strcmp(cmd[0], "export")))
		return (ft_execut_export(cmd), 1);

	else if(!(ft_strcmp(cmd[0], "unset")))
		return (ft_execut_unset(cmd), 1);

	else if(!(ft_strcmp(cmd[0], "env")))
		return(ft_execut_env(g_v.env), 1);

	else if(!ft_strcmp(cmd[0], "exit"))
	{
		if(ft_execut_exit(cmd))
			return (1);
	}
	}
	return(0);
}
