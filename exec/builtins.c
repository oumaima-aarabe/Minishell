/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 16:32:26 by azarda            #+#    #+#             */
/*   Updated: 2023/07/17 09:08:28 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	ft_execut_echo(char **tab, int i, int j, int bol)
{
	while (tab[i] && (ft_strncmp(tab[i], "-n", 2)) == 0)
	{
		j = 2;
		while (tab[i][j] && tab[i][j] == 'n')
			j++;
		if (tab[i][j] && tab[i][j] != 'n')
			break ;
		if (tab[i][j])
			bol = 1;
		else
			bol = 0;
		i++;
	}
	while (tab[i])
	{
		ft_putstr_fd(tab[i++], 1);
		if (tab[i] != NULL)
			ft_putstr_fd (" ", 1);
	}
	if (bol)
		ft_putstr_fd("\n", 1);
	g_v.ex_s = 0;
}

int	ft_execut_pwd(char *cmd, t_env *env)
{
	char	*pwd;

	if (cmd && cmd[0] == '-' && cmd[1])
	{
		ft_print_err("pwd", ": No take option\n");
		return (g_v.ex_s = 1, 1);
	}
	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		printf("%s\n", pwd);
		return (free(pwd), 1);
	}
	free(pwd);
	while (env)
	{
		if (!ft_strcmp("PWD", env->key))
			return (printf("%s\n", env->valu), 1);
		env = env->next;
	}
	printf("%s\n", g_v.pwd);
	return (0);
}

void	ft_free_plus(char *s1, char *s2, void *s3)
{
	free(s1);
	free(s2);
	free(s3);
}

void	ft_remov_lis(char *cmd)
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

void	ft_execut_unset(char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		if (ft_invalid_export_unset(cmd[i], "unset"))
		{
			i++;
			continue ;
		}
		ft_remov_lis (cmd[i]);
		i++;
	}
}

void	ft_execut_env(t_env *env, char **cmd)
{
	if (cmd[1])
	{
		if (cmd[1][0] == '-')
			ft_print_err(cmd[0], ": No take option\n");
		else
			ft_print_err(cmd[0], ": No take argument\n");
		g_v.ex_s = 1;
		return ;
	}
	while (env)
	{
		if (env->valu)
			printf("%s=%s\n", env->key, env->valu);
		env = env->next;
	}
}

int	ft_atoi_exit(char *str, int i)
{
	int		s;
	long	d;

	s = 1;
	d = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if(d > d * 10 + str[i] - '0')
				return(ft_print_err(str, \
		" : numeric argument required\n"), exit(255), 1);
		d = d * 10 + str[i] - '0';
		i++;
	}
	if (str[i] != '\0')
		return(ft_print_err(str, \
		" : numeric argument required\n"), exit(255), 1);
	return ((int)(d * s));
}

int	ft_execut_exit(char **cmd)
{
	int	nb;
	int	i;

	nb = 0;
	i = 0;
	printf("exit\n");
	if (cmd[1])
	{
		if (cmd[1][i])
		{
			nb = ft_atoi_exit(cmd[1], 0);
			if (cmd[1] && cmd[2])
			{
				ft_putstr_fd("Minishell exit: too many arguments\n", 2);
				g_v.ex_s = 1;
				return (1);
			}
		}
	}
	else
		exit(g_v.ex_s);
	exit(nb);
}

int	ft_execut_bultins(char **cmd)
{
	if (cmd && !ft_strcmp(cmd[0], "echo"))
		return (ft_execut_echo(cmd, 1, 0, 1), 1);
	if (cmd &&!ft_strcmp(cmd[0], "exit"))
	{
		if (ft_execut_exit(cmd))
			return (1);
	}
	g_v.ex_s = 0;
	if (cmd)
	{
		if (!ft_strcmp(cmd[0], "cd"))
			return (ft_execut_cd(cmd[1], g_v.env), 1);
		else if (!ft_strcmp(cmd[0], "pwd"))
			return (ft_execut_pwd(cmd[1], g_v.env), 1);
		else if (!(ft_strcmp(cmd[0], "export")))
			return (ft_execut_export(cmd), 1);
		else if (!(ft_strcmp(cmd[0], "unset")))
			return (ft_execut_unset(cmd), 1);
		else if (!(ft_strcmp(cmd[0], "env")))
			return (ft_execut_env(g_v.env, cmd), 1);
	}
	return (0);
}
