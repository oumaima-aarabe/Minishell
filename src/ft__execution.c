/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft__execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 07:13:45 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/19 04:28:10 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

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
