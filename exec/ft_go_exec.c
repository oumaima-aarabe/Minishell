/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_go_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:11:26 by azarda            #+#    #+#             */
/*   Updated: 2023/07/03 09:04:38 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"


int exec(char **cmd, t_env *env)
{
	if(ft_execut_bultins(cmd))
		return (exit(1), 1);
	ft_exec(cmd , env);
		return (1);
}

int ft_one_cmd(t_splitnode *cmd, t_env *env)
{
	int status;
	int pid;
	pid = 0;
	if(ft_execut_bultins(cmd->splitdata))
		return (-1);
	pid = fork();

	if(pid == -1)
		return(perror("Minishell: "), -1);
	if(pid == 0)
		ft_exec(cmd->splitdata , env);
	waitpid(pid, &status, 0);
	return (status);
}



int fork_execut(t_splitnode *ptr, t_fds pipe, t_env *env)
{
	int pid;

	// if(ptr->in != 0)
	// 	inp = ptr->in;
	// if(ptr->out != 1)
	// 	out = ptr->out;
	pid = fork();
	if(pid == -1)
		return(perror("Minishell "), -1);
	if(pid == 0)
	{
		if (pipe.in != 0)
		{
			dup2(pipe.in, 0);
			close(pipe.in);
		}
		if (pipe.out != 1)
		{
			dup2(pipe.out, 1);
			close(pipe.out);
		}
		if (pipe.fd_in != -1)
			close(pipe.fd_in);
		if (pipe.fd_out != -1)
			close(pipe.fd_out);
		exec(ptr->splitdata, env);
	}
	return(pid);
}



int ft_execut_cmd(t_splitnode *cmd)
{
	int fd[2];
	int dexieme_fd[2];
	int pid = 0;
	int status;


	if(!cmd->next)
		return (ft_one_cmd(cmd, g_v.env));
	else if (cmd->next)
	{
		pipe(fd);
		pid =  fork_execut(cmd, (t_fds){cmd->in, fd[1], fd[0], -1}, g_v.env);
		close(fd[1]);
		while(cmd->next->next != NULL)
		{
			pipe(dexieme_fd);
			pid =  fork_execut(cmd, (t_fds){fd[0], dexieme_fd[1], dexieme_fd[0], -1}, g_v.env);
			if(pid == -1)
				return (-1);
			close(fd[0]);
			fd[0] = dexieme_fd[0];
			close(dexieme_fd[1]);
			cmd = cmd->next;
		}
		cmd = cmd->next;
		pid = fork_execut(cmd, (t_fds){fd[0], cmd->out, -1, -1}, g_v.env);
		close(fd[0]);
		waitpid(pid, &status, 0);
		while(wait(NULL) != -1)
			;
	return (status);
	}
	return (-1); //
}



int phandle(int status)
{
    int new = WTERMSIG(status);
    if (new == SIGSEGV)
        ft_putstr_fd("yaha  segv ", 2);

    return (WTERMSIG(status) + 128);
}



int ft_exit_status(int	statu)
{
	// (void)statu;
	if (WIFEXITED(statu))
        return (g_v.ex_s = (WEXITSTATUS(statu)), 1);
	else if (WIFSIGNALED(statu))
        return (g_v.ex_s = phandle(statu));
	return (0);
}

void execution(t_splitnode *cmd)
{
	int statu;


	statu = ft_execut_cmd(cmd);
	// printf("%d\n", statu);
	// 	// if(statu == -1)
	// 	// {

	// 	// 	return ;
	// 	// }
	if (statu != -1)
		ft_exit_status(statu);
	printf("%d\n", g_v.ex_s);

}
