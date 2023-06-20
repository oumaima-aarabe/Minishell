/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_go_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:11:26 by azarda            #+#    #+#             */
/*   Updated: 2023/06/20 17:45:11 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

typedef struct s_fds
{
	int infile;
	int outfile;
}	t_fds;

int ft_execut_cmd(splitnode *cmd, t_env *env)
{
	unsigned int i = 0;
	// int pi;
	int fd[2];
	if (cmd && cmd->next)
	{
		while(cmd && cmd->next)
		{
			pipe(fd);
			if (cmd->out == -1)
				cmd->out = fd[1];
			if (cmd->in == -1)
				cmd->in = fd[0];
			if (i)
				cmd->in = cmd->prev->in;
			// ft_execut_bultins(cmd, env);
			if(ft_execut_bultins(cmd, env))
				;
			else
				ft_exec(cmd , env);
			close(fd[1]);
			if (i)
				close(cmd->in);
			cmd = cmd->next;
			i = !i;
		}
		if(ft_execut_bultins(cmd, env))
			;
		else
			ft_exec(cmd , env);
		close(fd[0]);
	}
	else
	{
		if(ft_execut_bultins(cmd, env))
			return 1;
		ft_exec(cmd , env);
		return (1);
	}
	return 0;
}
