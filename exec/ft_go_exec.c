/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_go_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:11:26 by azarda            #+#    #+#             */
/*   Updated: 2023/07/17 09:10:17 by ouaarabe         ###   ########.fr       */
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

int	wait_pid(int pid)
{
	int	status;

	if (pid != -1)
		waitpid(pid, &status, 0);
	while (wait(NULL) != -1)
		;
	return (status);
}

int	ft_execut_cmd(t_splitnode *cmd)
{
	int	fd[2];
	int	de_fd[2];
	int	pid;
	int	status;

	pipe(fd);
	pid = fork_execut(cmd, (t_fds){cmd->in, fd[1], fd[0], -1}, g_v.env);
	close(fd[1]);
		cmd = cmd->next;
	while (pid != -1 && cmd->next != NULL)
	{
		pipe(de_fd);
		pid = fork_execut(cmd, (t_fds){fd[0], de_fd[1], de_fd[0], -1}, g_v.env);
		close(fd[0]);
		fd[0] = de_fd[0];
		close(de_fd[1]);
		cmd = cmd->next;
	}
	if (pid != -1)
		pid = fork_execut(cmd, (t_fds){fd[0], cmd->out, -1, -1}, g_v.env);
	close(fd[0]);
	status = wait_pid(pid);
	if (pid == -1)
		return (-1);
	return (status);
}

int	check_child(int status)
{
	int	n_si;

	n_si = WTERMSIG(status);
	if (n_si == SIGSEGV)
		printf("Minishell : %s\n", "Segmentation fault");
	if (n_si == SIGQUIT)
		printf("Quit\n");
	if (n_si == SIGINT)
		printf("\n");
	return (WTERMSIG(status) + 128);
}

int	ft_exit_status(int statu)
{
	if (WIFEXITED(statu))
		return (g_v.ex_s = (WEXITSTATUS(statu)), 1);
	else if (WIFSIGNALED(statu))
		return (g_v.ex_s = check_child(statu));
	return (0);
}

void	execution(t_splitnode *cmd)
{
	int	statu;

	if (!cmd)
		return ;
	if (cmd && !cmd->next)
		statu = ft_one_cmd(cmd, g_v.env, 0, 0);
	else
		statu = ft_execut_cmd(cmd);
	if (statu == 0 && !cmd->splitdata)
		return ;
	if (statu != -1)
		ft_exit_status(statu);
}
