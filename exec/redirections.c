/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 10:54:49 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/17 07:22:32 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

bool is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

int	get_fl( char *str)
{

	// printf ("[%s]\n", str);
	int		length;
	t_quote cq;
	length = 0;

	ft_memset(&cq, 0, sizeof(t_quote));
	while (str[length])
	{
		cq = check_quotes(cq, length, str);
		if (!cq.ind && !cq.ins && (str[length] == '<' || str[length] == '>'))
			break; // Stop at red operator
		if (str[length])
			length++;
	}
	return length;
}

char *get_1redfilen(int *i, int *j, char **cmd_l, t_env *env)
{
	char *file_name = NULL;
	int file_len = 0;
	char *true_face = NULL;

	if (cmd_l[*i][*j + 1])
	{
		file_len = get_fl(&cmd_l[*i][*j + 1]);
		file_name = strndup(&cmd_l[*i][*j + 1], file_len);
		*j += file_len + 1;
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

char *get_2redfilen(int *i, int *j, char **cmd_l, t_env *env)
{
	char *file_name = NULL;
	char *true_face = NULL;
	int file_len = 0;

	if (cmd_l[*i][*j + 2])
	{
		file_len = get_fl(&cmd_l[*i][*j + 2]);
		file_name = strndup(&cmd_l[*i][*j + 2], file_len);
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

void red_append(t_splitnode **node, int *i, int *j, t_env *env)
{
	char *appfile = get_2redfilen(i, j, (*node)->splitdata, env);
	if (appfile)
	{
		
		int fd = open(appfile, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (fd == -1)
		{
			if (!g_v.red_flag)
			{
				ft_putstr_fd("Minishell: ", 2);
				perror(appfile);
				g_v.red_flag = 1;
				(*node)->out = -2;
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

void red_input(t_splitnode **node, int *i, int *j, t_env *env)
{
	char *infile = get_1redfilen(i, j, (*node)->splitdata, env);
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

void red_output(t_splitnode **node, int *i, int *j, t_env *env)
{
	char *outfile = get_1redfilen(i, j, (*node)->splitdata, env);
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

void	hr_loop(t_splitnode *c, t_quote cq, t_env *env, int *i)
{
	while (c->splitdata[*i][cq.j] && !g_v.red_flag)
	{
		cq = check_quotes(cq,cq.j, c->splitdata[*i]);
		if (!cq.ind && !cq.ins && !is_quote(c->splitdata[*i][cq.j]))
		{
			if (c->splitdata[*i][cq.j] == '<' && c->splitdata[*i][cq.j + 1] != '<')
			{
				red_input(&c, i, &cq.j, env);
				continue;
			}
			else if (c->splitdata[*i][cq.j] == '>' && c->splitdata[*i][cq.j + 1] != '>')
			{
				red_output(&c, i, &cq.j, env);
				continue;
			}
			else if (c->splitdata[*i][cq.j] == '>' && c->splitdata[*i][cq.j + 1] == '>')
			{
				red_append(&c, i, &cq.j, env);
					continue;
			}
		}
			cq.j++;
	}
}

t_splitnode *handle_redirections(t_splitnode *node, t_env *env)
{
	t_splitnode *current;
	t_splitnode *trimmed;
	t_quote		cq;
	int			i;

	current = node;
	trimmed = NULL;
	while (current != NULL)
	{
		g_v.red_flag = 0;
		i = 0;
		if (current->splitdata)
		{
			while (current->splitdata[i] && !g_v.red_flag)
			{
				ft_memset(&cq, 0, sizeof(t_quote));
				hr_loop(current, cq, env, &i);
				i++;
			}
		}
		current = current->next;
	}
	trimmed = remove_redirections(node, 0);
	free_split_nodes(node);
	return trimmed;
}
/////////////////////////////////////////////////////////
