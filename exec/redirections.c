/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 10:54:49 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/18 08:16:48 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

char	*get_1redfilen(int *i, int *j, char **cmd_l, t_env *env)
{
	char	*file_name;
	int		file_len;
	char	*true_face;

	file_name = NULL;
	file_len = 0;
	true_face = NULL;
	if (cmd_l[*i][*j + 1])
	{
		file_len = get_fl(&cmd_l[*i][*j + 1]);
		file_name = strndup(&cmd_l[*i][*j + 1], file_len); // ! strndup akhra
		*j += file_len + 1;
	}
	else if (cmd_l[*i + 1] && ft_strlen(cmd_l[*i + 1]) > 0)
	{
		*j = 0;
		file_len = get_fl(cmd_l[*i + 1]);
		file_name = strndup(cmd_l[*i + 1], file_len); //! hi  strndup
		*i += 1;
		*j += file_len;
	}
		true_face = removequotes(ft_expand(file_name, env));
	return (true_face);
}

char	*get_2redfilen(int *i, int *j, char **cmd_l, t_env *env)
{
	char	*file_name;
	char	*true_face;
	int		file_len;

	file_name = NULL;
	true_face = NULL;
	file_len = 0;
	if (cmd_l[*i][*j + 2])
	{
		file_len = get_fl(&cmd_l[*i][*j + 2]);
		file_name = strndup(&cmd_l[*i][*j + 2], file_len); // ! yaha w7da akhra
		*j += file_len + 2;
	}
	else if (cmd_l[*i + 1] && ft_strlen(cmd_l[*i + 1]) > 0)
	{
		*j = 0;
		file_len = get_fl(cmd_l[*i + 1]);
		file_name = strndup(cmd_l[*i + 1], file_len);
		*i += 1;
		*j += file_len;
	}
		true_face = removequotes(ft_expand(file_name, env));
	return (true_face);
}

void	red_append(t_splitnode **node, int *i, int *j, t_env *env)
{
	char	*appfile = get_2redfilen(i, j, (*node)->splitdata, env);
	if (appfile)
	{
		int	fd = open(appfile, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (fd == -1)
		{
			if (!g_v.red_flag)
			{
				ft_putstr_fd("Minishell: ", 2);
				perror(appfile);
				g_v.red_flag = 1;
				(*node)->out = -2;
				g_v.ex_s = 1;
			}
		}
		else
		{
			if ((*node)->out != -1)
				close((*node)->out);
			(*node)->out = fd;
		}
		free(appfile);
	}
}

void	red_input(t_splitnode **node, int *i, int *j, t_env *env)
{
	char	*infile = get_1redfilen(i, j, (*node)->splitdata, env);

	if (infile)
	{
		int fd = open(infile, O_RDONLY);
		if (fd == -1)
		{
			if (!g_v.red_flag)
			{
				ft_putstr_fd("Minishell: ", 2);
				perror(infile);
				g_v.red_flag = 1;
				(*node)->in = -2;
				g_v.ex_s = 1;
			}
		}
		else
		{
			if ((*node)->in != -1)
				close((*node)->in);
			(*node)->in = fd;
		}
		free(infile);
	}
}

void	red_output(t_splitnode **node, int *i, int *j, t_env *env)
{
	char	*outfile = get_1redfilen(i, j, (*node)->splitdata, env);

	if (outfile)
	{
		int fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			if (!g_v.red_flag)
			{
				ft_putstr_fd("Minishell: ", 2);
				perror(outfile);
				g_v.red_flag = 1;
				(*node)->out = -2;
				g_v.ex_s = 1;
			}
		}
		else
		{
			if ((*node)->out != -1)
				close((*node)->out);
			(*node)->out = fd;
		}
		free(outfile);
	}
}


