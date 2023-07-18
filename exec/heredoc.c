/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:08:33 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/18 14:24:53 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	handle_c(int sig)
{
	(void)sig;
	g_v.ex_s = 1;
	g_v.sig_flag = 1;
	rl_on_new_line();
	rl_replace_line("", 0);
	ioctl(0, TIOCSTI, "\4");
}

char	*gethd_redfilen(int *i, int *j, char **cmd_l)
{
	char	*file_name;
	int		file_len;

	file_name = NULL;
	file_len = 0;
	if (cmd_l[*i][*j + 2])
	{
		file_len = get_fl(&cmd_l[*i][*j + 2]);
		file_name = ft_strndup(&cmd_l[*i][*j + 2], file_len);
		*j += file_len;
	}
	else if (cmd_l[*i + 1] && ft_strlen(cmd_l[*i + 1]) > 0)
	{
		*j = 0;
		file_len = get_fl(cmd_l[*i + 1]);
		file_name = ft_strndup(cmd_l[*i + 1], file_len);
		*i += 1;
		*j += file_len;
	}
	return (file_name);
}

void	read_inhd(char *lmtr, int k, int fd, t_env *env)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline("$> ");
		if (!line || !ft_strcmp(line, lmtr))
		{
			free (line);
			break ;
		}
		if (!k)
			line = ft_expand(line, env);
		ft_putendl_fd(line, fd);
		free(line);
	}
}

t_splitnode	*read_hd(t_splitnode *current, int *i, int *j, t_env *env)
{
	int		fd[2];
	char	*lmtr;
	char	*tmp;
	int		k;

	lmtr = gethd_redfilen(i, j, current->splitdata);
	tmp = ft_strdup(lmtr);
	lmtr = removequotes(lmtr);
	k = ft_strcmp(lmtr, tmp);
	if (pipe(fd) < 0)
		return (current);
	g_v.sig_flag = 0;
	signal(SIGINT, handle_c);
	signal(SIGQUIT, SIG_IGN);
	read_inhd(lmtr, k, fd[1], env);
	close (fd[1]);
	free(lmtr);
	free(tmp);
	if (current->in != -1)
		close(current->in);
	if (g_v.sig_flag)
		return (close(fd[0]), current);
	current->in = fd[0];
	return (current);
}
