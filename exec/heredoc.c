/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:08:33 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/08 22:38:32 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	read_hd(char **cmdl, int *in, int *i, int *j, t_env *env)
{
	int fd[2];
	char *lmtr = get_redfilen(i, j, cmdl, "<<", env);
	char *tmp = lmtr;
	int k;

	lmtr = removequotes(lmtr);
	k = ft_strcmp(lmtr, tmp);
	char *line = NULL;
	if (pipe(fd) < 0)
		return ;
	if (!fork())
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		// close(fd[0]);
		while (1)
		{
			line = readline("$> ");
			if (!line || !strcmp(line, lmtr))
				exit(0);
			if (!k)
			{
				line = ft_expand(line, env);
				// puts("here");
			}
			ft_putendl_fd(line, fd[1]);
			free(line);
		}
	}
	close (fd[1]);
	wait(NULL);
	free(lmtr);
	*in = fd[0];
}

t_splitnode *handle_heredoc(t_splitnode *node, t_env *env)
{
	t_splitnode *current = node;
	t_splitnode *trimmed;
	while (current != NULL)
	{
		char **cmdl = current->splitdata;
		int i = 0;

		while (cmdl[i])
		{
			int j = 0;
			bool inside_quotes = false;

			while (cmdl[i][j])
			{
				if (!inside_quotes && !is_quote(cmdl[i][j]))
					if (cmdl[i][j] == '<' && cmdl[i][j + 1] == '<')
						read_hd(cmdl, &current->in, &i, &j, env);
				if (is_quote(cmdl[i][j]))
					inside_quotes = !inside_quotes;
				if (cmdl[i][j])
					j++;
			}
			i++;
		}
		current = current->next;
	}
	trimmed = remove_redirections(node, 1);
	free_split_nodes(node);
	return trimmed;
}

int wc_heredoc(char **cmdl)
{
	int i = 0;
    int wc = 0;
    bool print = false;

 	while (cmdl[i])
	{
		int j = 0;
		bool inside_quotes = false;
		while (cmdl[i][j])
		{
			if (ft_strncmp("<<", &cmdl[i][j], 2))
				print = true;
			if (!inside_quotes && !is_quote(cmdl[i][j]))
			{
				if (cmdl[i][j] == '<' && cmdl[i][j + 1] == '<')
				{
					if (cmdl[i][j + 2])
						j +=   get_fl(&cmdl[i][j + 2]) + 1;
					else if (cmdl[i + 1])
						j = get_fl(cmdl[++i]);}
			}

			if (is_quote(cmdl[i][j]))
				inside_quotes = !inside_quotes;
			if (cmdl[i][j])
				j++;
		}
		if (print)
		{
			wc++;
			print = false;
		}
		i++;
	}
	return (wc);
}


char **ns_heredoc(char **cmdl, int wc)
{
    char **new_s;
    int i = 0;
    int j;
    int count = 0;
    bool print = false;
    int k = 0;
    int z;


    new_s = (char **)ft_calloc((wc + 1) , sizeof(char *));
     while (cmdl[i] && i < wc)
    {
        j = 0;
        bool inside_quotes = false;
        while (cmdl[i][j])
        {
            if (inside_quotes || strncmp("<<", &cmdl[i][j], 2))
            {
                print = true;
                z = i;
                count++;
            }
            if (!inside_quotes && !is_quote(cmdl[i][j]))
            {
                if (cmdl[i][j] == '<' && cmdl[i][j + 1] == '<')
                {
                    if (cmdl[i][j + 2])
                    j +=   get_fl(&cmdl[i][j + 2]) + 1;
                    else if (cmdl[i + 1])
                    j = get_fl(cmdl[++i]);
                }
            }
            if (cmdl[i][j])
            {
                if (is_quote(cmdl[i][j]))
                    inside_quotes = !inside_quotes;
                j++;
            }
        }
        if (print)
        {
            new_s[k] = (char *)ft_calloc((count + 1) , sizeof(char ));
            j = 0;
            while (j < count)
            {
                new_s[k][j] = cmdl[z][j];
                j++;
            }
            new_s[k][j] = '\0';
            k++;
            print = false;
            count = 0;
        }
        i++;
    }
        return new_s;
}
