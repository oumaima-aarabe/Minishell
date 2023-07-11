/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 16:32:26 by azarda            #+#    #+#             */
/*   Updated: 2023/07/11 04:11:13 by azarda           ###   ########.fr       */
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


void ft_execut_cd(char *str, t_env *env)
{

	t_env *tmp = env;
	t_env *tmp_1 = env;
	char *old;
	char *pwd;
	char *hom;

	old = NULL;
	hom = NULL;
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
	if(!old)
			old = getcwd(NULL, 0);

		if(!str)
		{
			if(!hom)
			{
				ft_putstr_fd("minishell: cd: HOME not set\n", 2);
				// ex_s = 1;
 			}
			if(chdir(hom) < 0)
			{
				ft_putstr_fd("minishell: cd: ", 2);
				perror(hom);
				// printf()
			}
		}
		else if(str[0] == '-' && str[1] == '\0')
		{
			while (tmp_1)
			{
				if(!ft_strcmp(tmp_1->key, "OLDPWD"))
				{
					if(chdir(tmp_1->valu) < 0)
					{
						ft_putstr_fd("minishell: cd: ", 2);
						perror(str);
						// ex_s = 1;
						break;
					}
					printf("%s\n",tmp_1->valu);
					break;
				}
				tmp_1 = tmp_1->next;
			}
			if(!tmp_1)
			{
				ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
				// ex_s = 1;
			}

		}
		else if(chdir(str) < 0)
		{
			ft_putstr_fd("minishell: cd: ", 2);
			perror(str);
			// ex_s = 1;
		}

		pwd = getcwd(NULL, 0);
		if(pwd == NULL)
		{
			ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
			free(pwd);
			// free(old);
			return ;
		}
		free(pwd);



//----------------------------------------------------------------

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
			tmp->valu = ft_strdup(old);
		}
		tmp = tmp->next;
	}
	free(old);
//----------------------------------------------------------------
}

//____________________________________pwd_________________________________________

void ft_ft_execut_pwd(char *cmd, t_env *env)
{
	char *pwd;
	(void)cmd;
	// (void)outfile;

	// if(cmd && cmd[0] == '-' && cmd[1])
	// {
	// 	ft_print_err("minishell: pwd:" ,cmd,  ": invalid option\n");
	// 	ex_s = 1;
	// 	return;
	// }
	// puts("hgfd");
	pwd = getcwd(NULL, 0);
	if(pwd)
	{
		printf("%s\n", pwd);
		// write(outfile, pwd, ft_strlen(pwd));
		free(pwd);
		return ;
	}
	while(env)
	{
		if(!ft_strcmp("PWD", env->key))
		{
			// write(outfile, env->valu, ft_strlen(env->valu));
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

int	ft_invalid_export_unset(char *cmd, char *bult)
{
	if(cmd && is_alphabet(cmd[0]) && cmd[0] != '_')
	{
		if(cmd[0] == '-') // cheack option dir tlila fsubject problem in g_v
			ft_print_err(cmd , "  invalid option\n");
		else
			ft_print_err(cmd , " : not a valid identifier\n");
		g_v.ex_s = 1;
		return 1;
	}
	if(cmd && !ft_sine(cmd, '=') && ft_sine(cmd, '+'))
	{
		if((cmd[ft_sine(cmd , '+') + 1] != '='))
		{
			ft_print_err(cmd , " : not a valid identifier\n");
			g_v.ex_s = 1;
			return 1;
		}
	}
	if(!ft_strcmp(bult, "unset") && (ft_sine(cmd, '+') || ft_sine(cmd, '=')))
	{
		ft_print_err(cmd , " : not a valid identifier\n");
		g_v.ex_s = 1;
		return (1);
	}
	return (0);
}

char *ft_new_key(char *cmd)
{
	int i = 0;
	char *new_key = NULL;

	if(cmd)
	{
		if (ft_sine(cmd, '='))
		{
			i = ft_sine(cmd, '=');
			if(cmd[i - 1] == '+')
				i -= 1;
			new_key = ft_substr(cmd, 0, i);
			return(new_key);
		}
	}
	return (ft_strdup(cmd));
}

int ft_cheak_old_env(char *cmd)
{
	int i = 0;
	char *new_key;
	t_env *tmp;

	tmp = g_v.env;
	new_key = ft_new_key(cmd);
	if(new_key[0] == '_')
		return (free(new_key),  1);
	i = ft_sine(cmd, '=');
	while(cmd && tmp)
	{
		if(!ft_strcmp(new_key, tmp->key))
		{
			if(i && cmd[i - 1] == '+')
			{
				puts("--->>1<<----");
				tmp->valu =  ft_strjoin(tmp->valu, ft_substr(cmd, i + 1, (ft_strlen(cmd) - i))); // ha wa7d liksa
			}
			else if (i) // ila kant = bo7dha makanch +
			{
				puts("--->>2<<----");
				free(tmp->valu);
				tmp->valu = ft_substr(cmd, i + 1, (ft_strlen(cmd) - i));
			}
			return (free(new_key),1);
		}
		tmp = tmp->next;
	}
	return (free(new_key),1);
}

int ft_cheak_expor(char *cmd)
{
	// if(cmd && cmd[0] == '_' && (cmd[1] == '=' || cmd[1] == '+'))
	// {
	// 	// printf(" >> %s\n", cmd);
	// 	return (1);
	// }
	if(ft_invalid_export_unset(cmd, "export"))
		return (1);
	if(ft_cheak_old_env(cmd))
		return (1);

	return 0;
}

int ft_add_export(char *cmd)
{
	int j = 0;
		if(ft_sine(cmd, '='))
		{
			j = ft_sine(cmd, '=');
			if(cmd[j - 1] == '+')
				ft_lstadd_back(&g_v.env,ft_creat(ft_substr(cmd, 0, j - 1), ft_substr(cmd, j + 1, ft_strlen(cmd) - j)));
			else
				ft_lstadd_back(&g_v.env,ft_creat(ft_substr(cmd, 0, j), ft_substr(cmd, j + 1, ft_strlen(cmd) - j)));
		}
		else
			ft_lstadd_back(&g_v.env, ft_creat(ft_strdup(cmd), NULL));
	return (1);
}

int ft_cheack_add_export(char **cmd)
{
	int i;

	i = 1;
	while(cmd[i])
	{
		if(ft_cheak_expor(cmd[i]))
		{
			if(cmd[i + 1])
			{
				i++;
				continue;
			}
			return 1;
		}
		if (ft_add_export(cmd[i]))
		{
			if(cmd[i + 1])
			{
				i++;
				continue;
			}
			return 1;
		}
		i++;
	}
	return (0);
}

t_env *ft_sort_export(t_env *tmp)
{
	t_env *tmp1;
	char 	*swap;

	tmp1 = tmp;
	while(tmp && tmp->next != NULL)
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
	return (tmp);
}

void  ft_execut_export(char **cmd)
{
	t_env *tmp;
	t_env *tmp1;

	if(ft_cheack_add_export(cmd))
		return ;

	tmp = duplicate_linked_list(g_v.env);
	tmp = ft_sort_export(tmp);
	tmp1 = tmp;
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
		if(cmd[i][0] == '_' && cmd[i][1] == '\0')
		{
			printf("-->> %s\n", cmd[i]);
			i++;
			continue;
		}
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
		ft_print_err(str,  " numeric argument required\n");
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
		return (ft_execut_echo(cmd), 1);

	else if(!ft_strcmp(cmd[0], "cd"))
		return (ft_execut_cd(cmd[1], g_v.env),  1);

	else if(!ft_strcmp(cmd[0], "pwd"))
		return (ft_ft_execut_pwd(cmd[1] ,g_v.env), 1);

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
