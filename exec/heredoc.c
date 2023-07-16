/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:08:33 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/15 10:58:31 by ouaarabe         ###   ########.fr       */
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

void	read_inhd(char *lmtr, int k, int fd, t_env *env)
{
	char *line = NULL;
	while (1)
	{
		line = readline("$> ");
		if (!line || !strcmp(line, lmtr))
		{
			free (line);
			break;
		}
		if (!k)
			line = ft_expand(line, env);
		ft_putendl_fd(line, fd);
		free(line);
	}
}
char *gethd_redfilen(int *i, int *j, char **cmd_l)
{
	char *file_name = NULL;
	int file_len = 0;

	if (cmd_l[*i][*j + 2])
	{
		file_len = get_fl(&cmd_l[*i][*j + 2]);
		file_name = strndup(&cmd_l[*i][*j + 2], file_len);
		*j += file_len;
	}
	else if (cmd_l[*i + 1] && ft_strlen(cmd_l[*i + 1]) > 0)
	{
		*j = 0;
		file_len = get_fl(cmd_l[*i + 1]);
		file_name = strndup(cmd_l[*i + 1], file_len);
		*i += 1;
		*j += file_len;
	}
		return (file_name);
}
t_splitnode	*read_hd(t_splitnode *current, int *i, int *j, t_env *env)
{
	int fd[2];
	char *lmtr = gethd_redfilen(i, j, current->splitdata);
	char *tmp = ft_strdup(lmtr);
	int k;

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
	if (g_v.sig_flag)
	{
		close(fd[0]);
		return (current);
	}
	current->in = fd[0];
	return (current);
}

t_splitnode *handle_heredoc(t_splitnode *node, t_env *env)
{
	t_splitnode *current;
	t_splitnode *trimmed;
	t_quote		cq;

	current = node;
	while (current != NULL)
	{
		int i = 0;
		while (current->splitdata[i])
		{
			int j = 0;
			ft_memset(&cq, 0, sizeof(t_quote));

			while (current->splitdata[i][j])
			{
				cq = check_quotes(cq,j, current->splitdata[i]);
				if (!cq.in_dquotes && !cq.in_squotes && !is_quote(current->splitdata[i][j]))
					if (current->splitdata[i][j] == '<' && current->splitdata[i][j + 1] == '<')
						current = read_hd(current, &i, &j, env);
				if (current->splitdata[i][j])
					j++;
			}
			if (current->splitdata[i])
				i++;
		}
		current = current->next;
	}
	trimmed = remove_redirections(node, 1);
	free_split_nodes(node);
	return trimmed;
}

t_hd	check_dprintable(char **cmdl, t_quote cq, t_hd hd)
{
	if (ft_strncmp("<<", &cmdl[hd.i][hd.j], 2))
		hd.print = true;
	if (!cq.in_dquotes && !cq.in_squotes && !is_quote(cmdl[hd.i][hd.j]))
	{
		if (cmdl[hd.i][hd.j] == '<' && cmdl[hd.i][hd.j + 1] == '<')
		{
			if (cmdl[hd.i][hd.j + 2])
				hd.j +=   get_fl(&cmdl[hd.i][hd.j + 2]) + 1;
			else if (cmdl[hd.i + 1])
				hd.j = get_fl(cmdl[++hd.i]);}
	}

	if (is_quote(cmdl[hd.i][hd.j]))
		cq = check_quotes(cq, hd.j, cmdl[hd.i]);
	if (cmdl[hd.i][hd.j])
		hd.j++;
	return (hd);
}

int wc_heredoc(char **cmdl)
{
	t_hd	hd;
	t_quote cq;

	ft_memset(&hd, 0, sizeof(t_hd));
 	while (cmdl[hd.i])
	{
		hd.j = 0;
		ft_memset(&cq, 0, sizeof(t_quote));
		while (cmdl[hd.i][hd.j])
		{
			cq = check_quotes(cq,hd.j, cmdl[hd.i]);
			hd = check_dprintable(cmdl, cq, hd);
			cq = check_quotes(cq,hd.j, cmdl[hd.i]);
		}
		if (hd.print)
		{
			hd.wc++;
			hd.print = false;
		}
		hd.i++;
	}
	return (hd.wc);
}

t_hd	numerate(t_hd hd)
{
	hd.print = 1;
	hd.z = hd.i;
	hd.count++;
	return (hd);
}

t_hd	check_printable(char **cmdl, t_quote cq, t_hd hd)
{
	while (cmdl[hd.i][hd.j])
	{
		cq = check_quotes(cq,hd.j, cmdl[hd.i]);
		if ((cq.in_dquotes || cq.in_squotes) || strncmp("<<", &cmdl[hd.i][hd.j], 2))
			hd = numerate(hd);
		if (!cq.in_dquotes && !cq.in_squotes && !is_quote(cmdl[hd.i][hd.j]))
		{
			if (cmdl[hd.i][hd.j] == '<' && cmdl[hd.i][hd.j + 1] == '<')
			{
				if (cmdl[hd.i][hd.j + 2])
				hd.j +=   get_fl(&cmdl[hd.i][hd.j + 2]) + 1;
				else if (cmdl[hd.i + 1])
				hd.j = get_fl(cmdl[++hd.i]);
			}
		}
		if (cmdl[hd.i][hd.j])
		{
			if (is_quote(cmdl[hd.i][hd.j]))
				cq = check_quotes(cq, hd.j, cmdl[hd.i]);
			hd.j++;
		}
	}
	return(hd);
}

char	*fill_ns_hd(char *cmdl, int count)
{
	char *new_s;
	int j;
	
	j = 0;
	new_s = (char *)ft_calloc((count + 1) , sizeof(char ));
	if (!new_s)
		return (NULL);
	while (j < count)
	{
		new_s[j] = cmdl[j];
		j++;
	}
	return (new_s);
}
char **ns_heredoc(char **cmdl, int wc)
{
    char 	**new_s;
   	t_hd	hd;
	t_quote cq;

	ft_memset(&hd, 0, sizeof(t_hd));
    new_s = (char **)ft_calloc((wc + 1) , sizeof(char *));
    while (cmdl[hd.i])
    {
        hd.j = 0;
        ft_memset(&cq, 0, sizeof(t_quote));
        while (cmdl[hd.i][hd.j])
        {
			cq = check_quotes(cq,hd.j, cmdl[hd.i]);
			hd = check_printable(cmdl, cq, hd);
			cq = check_quotes(cq,hd.j, cmdl[hd.i]);
        }
        if (hd.print)
		{
            new_s[hd.k++] = fill_ns_hd(cmdl[hd.z], hd.count);
			hd.print = 0;
			hd.count = 0;	
		}
        hd.i++;
    }
        return new_s;
}
