/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_go_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:11:26 by azarda            #+#    #+#             */
/*   Updated: 2023/07/18 07:14:13 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	exec(char **cmd, t_env *env, t_fds pipe)
{
	if (pipe.in != -1)
	{
		dup2(pipe.in, 0);
		close(pipe.in);
	}
	if (pipe.out != -1)
	{
		dup2(pipe.out, 1);
		close(pipe.out);
	}
	if (pipe.fd_in != -1)
		close(pipe.fd_in);
	if (pipe.fd_out != -1)
		close(pipe.fd_out);
	if (ft_execut_bultins(cmd))
		return (exit(0), 1);
	ft_exec(cmd, env);
	return (1);
}

int	ft_ex_bult_close(t_splitnode *cmd, int fd_in, int fd_out)
{
	if (ft_execut_bultins(cmd->splitdata))
	{
		if (cmd->in != -1)
		{
			dup2(fd_in, 0);
			close(fd_in);
		}
		if (cmd->out != -1)
		{
			dup2(fd_out, 1);
			close(fd_out);
		}
		return (1);
	}
	return (0);
}

int	wait_close(t_splitnode *cmd, int pid, int fd_in, int fd_out)
{
	int	status;

	waitpid(pid, &status, 0);
	if (cmd->in != -1)
	{
		dup2(fd_in, 0);
		close(fd_in);
	}
	if (cmd->out != -1)
	{
		dup2(fd_out, 1);
		close(fd_out);
	}
	return (status);
}

int	ft_one_cmd(t_splitnode *cmd, t_env *env, int fd_in, int fd_out)
{
	int	pid;

	if (cmd->in != -1)
	{
		fd_in = dup(0);
		dup2(cmd->in, 0);
		close(cmd->in);
	}
	if (cmd->out != -1)
	{
		fd_out = dup(1);
		dup2(cmd->out, 1);
		close(cmd->out);
	}
	if (ft_ex_bult_close(cmd, fd_in, fd_out))
		return (-1);
	pid = fork();
	if (pid == -1)
		return (perror("Minishell "), g_v.ex_s = 1, -1);
	if (pid == 0)
		ft_exec(cmd->splitdata, env);
	return (wait_close(cmd, pid, fd_in, fd_out));
}

int	fork_execut(t_splitnode *ptr, t_fds pipe, t_env *env)
{
	int	pid;

	if (!ptr)
		return (-1);
	if (ptr->in != -1)
		pipe.in = ptr->in;
	if (ptr->out != -1)
		pipe.out = ptr->out;
	pid = fork();
	if (pid == -1)
		return (perror("Minishell "), g_v.ex_s = 1, -1);
	if (pid == 0)
		exec(ptr->splitdata, env, pipe);
	if (ptr->in != -1)
		close(ptr->in);
	if (ptr->out != -1)
		close(ptr->out);
	return (pid);
}
