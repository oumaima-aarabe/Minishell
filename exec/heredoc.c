/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:08:33 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/17 06:51:32 by ouaarabe         ###   ########.fr       */
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
t_splitnode	*read_hd(t_splitnode *current, int *i, int *j, t_env *env)
{
	int fd[2];
	char *lmtr;
	char *tmp;
	int k;

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

void	hh_loop(t_splitnode *c, t_env *env)
{
	int i;
	int j;
	t_quote cq;

	i = 0;
	while (c->splitdata[i])
	{
		j = 0;
		ft_memset(&cq, 0, sizeof(t_quote));
		while (c->splitdata[i][j])
		{
			cq = check_quotes(cq,j, c->splitdata[i]);
			if (!cq.ind && !cq.ins && !is_quote(c->splitdata[i][j]))
				if (c->splitdata[i][j] == '<' && c->splitdata[i][j + 1] == '<')
				{	
					c = read_hd(c, &i, &j, env);
					continue ;
				}
			if (c->splitdata[i][j])
				j++;
		}
		if (c->splitdata[i])
			i++;
	}
}

t_splitnode *handle_heredoc(t_splitnode *node, t_env *env)
{
	t_splitnode *c;
	t_splitnode *trimmed;

	c = node;
	while (c != NULL)
	{
		hh_loop(c, env);
		c = c->next;
	}
	trimmed = remove_redirections(node, 1);
	free_split_nodes(node);
	return trimmed;
}

t_hd	check_dprintable(char **cmdl, t_quote cq, t_hd hd)
{
	if ((cq.ind || cq.ins) || ft_strncmp("<<", &cmdl[hd.i][hd.j], 2))
		hd.print = true;
	if (!cq.ind && !cq.ins && !is_quote(cmdl[hd.i][hd.j]))
	{
		if (cmdl[hd.i][hd.j] == '<' && cmdl[hd.i][hd.j + 1] == '<')
		{
			if (cmdl[hd.i][hd.j + 2])
				hd.j +=   get_fl(&cmdl[hd.i][hd.j + 2]) + 2;
			else if (cmdl[hd.i + 1])
				hd.j = get_fl(cmdl[++hd.i]);
			return (hd);
		}
	}
	if (cmdl[hd.i][hd.j])
	{
		if (is_quote(cmdl[hd.i][hd.j]))
			cq = check_quotes(cq, hd.j, cmdl[hd.i]);
		hd.j++;	
	}
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
		}
		if (hd.print)
		{
			hd.wc++;
			hd.print = false;
		}
		hd.i++;
	}
	printf("wc : %d\n", hd.wc);
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
		if ((cq.ind || cq.ins) || strncmp("<<", &cmdl[hd.i][hd.j], 2))
			hd = numerate(hd);
		if (!cq.ind && !cq.ins && !is_quote(cmdl[hd.i][hd.j]))
		{
			if (cmdl[hd.i][hd.j] == '<' && cmdl[hd.i][hd.j + 1] == '<')
			{
				if (cmdl[hd.i][hd.j + 2])
				hd.j += get_fl(&cmdl[hd.i][hd.j + 2]) + 2;
				else if (cmdl[hd.i + 1])
				{
					printf("b; %c\n", cmdl[hd.i][hd.j]);
					hd.j = get_fl(cmdl[++hd.i]);
					printf("a: %c\n", cmdl[hd.i][hd.j]);
					hd.contin = hd.j;
				}
				continue;
			}
		}
		if (cmdl[hd.i][hd.j])
			hd.j++;
	}
	return(hd);
}

char	*fill_ns_hd(char *cmdl, int count, t_quote cq, t_hd hd)
{
	char *new_s;
	int j;
	int z;
	
	j = 0;
	z = 0;
	new_s = (char *)ft_calloc((count + 1) , sizeof(char ));
	if (!new_s)
		return (NULL);
	while (j < count && cmdl[z])
	{
		cq = check_quotes(cq, z, cmdl);
		if ((!cq.ind && !cq.ins) && !strncmp("<<", &cmdl[z], 2))
			if (cmdl[j + 2])
				z += get_fl(&cmdl[z + 2]) + 2;
			if (hd.contin)
			{
				z = hd.contin;
				hd.contin = 0;
			}
		new_s[j] = cmdl[z];
		j++;
		if (cmdl[z])
			z++;
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
		hd = check_printable(cmdl, cq, hd);
        if (hd.print)
		{
            new_s[hd.k++] = fill_ns_hd(cmdl[hd.z], hd.count, cq, hd);
			hd.print = 0;
			hd.count = 0;	
		}
        hd.i++;
    }
        return new_s;
}
