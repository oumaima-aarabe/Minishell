/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_go_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:11:26 by azarda            #+#    #+#             */
/*   Updated: 2023/07/12 01:52:48 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"


int exec(char **cmd, t_env *env)
{
	if(ft_execut_bultins(cmd))
		return (exit(0), 1);
	ft_exec(cmd , env);
		return (1);
}

int ft_one_cmd(t_splitnode *cmd, t_env *env)
{
	int status;
	int pid;
	pid = 0;
	int fd_out = -1;
	int fd_in = -1;

	if(cmd->in != -1)
	{
		fd_in = dup(0);
		dup2(cmd->in, 0);
		close(cmd->in);
	}
	if(cmd->out != -1)
	{
		fd_out = dup(1);
		dup2(cmd->out, 1);
		close(cmd->out);
	}
	if(ft_execut_bultins(cmd->splitdata))
	{

		if(cmd->in != -1)
		{
		dup2(fd_in, 0);
		close(fd_in);
		}
		if(cmd->out != -1)
		{
		dup2(fd_out, 1);
		close(fd_out);
		}
		return (-1);
	}
	pid = fork();
	if(pid == -1)
		return(perror("Minishell: "), -1);
	if(pid == 0)
		ft_exec(cmd->splitdata , env);
	waitpid(pid, &status, 0);
	if(cmd->in != -1)
	{
	dup2(fd_in, 0);
	close(fd_in);
	}
	if(cmd->out != -1)
	{
	dup2(fd_out, 1);
	close(fd_out);
	}
	return (status);
}



int fork_execut(t_splitnode *ptr, t_fds pipe, t_env *env)
{
	int pid;
	// puts("____________________________________");
	// printf("in  -->> %d\n", ptr->in);
	// printf("out -->> %d\n", ptr->out);
	// puts("____________________________________");
	if(!ptr)
		return (-1);
	// if(!ptr->splitdata || (ptr->splitdata && !ptr->splitdata[0]))
	// 	return (0);
	if(ptr->in != -1)
		pipe.in = ptr->in;
	if(ptr->out != -1)
		pipe.out = ptr->out;

	pid = fork();
	if(pid == -1)
	{

		puts("i = 1");
		return(perror("Minishell "), -1);
	}
	if(pid == 0)
	{
		if (pipe.in != -1)
		{
			dup2(pipe.in, 0);
			close(pipe.in);
		}
		if (pipe.out != -1) //ila kan -1
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


	if(!cmd)
		return(-1);
	// if(cmd && (!cmd->splitdata || (cmd->splitdata && !cmd->splitdata[0])))
	// 	return (-1);
	// if(!cmd->splitdata[0])
	// 	return (-1);

	if(cmd && !cmd->next)
			return (ft_one_cmd(cmd, g_v.env)); // ft_one_cd return -1 if execut bulti


		pipe(fd);
		pid =  fork_execut(cmd, (t_fds){cmd->in, fd[1], fd[0], -1}, g_v.env);

		close(fd[1]);
		// if(cmd->next->next)
			cmd = cmd->next;


		while(cmd->next != NULL)
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
		pid = fork_execut(cmd, (t_fds){fd[0], cmd->out, -1, -1}, g_v.env);
		close(fd[0]);
		waitpid(pid, &status, 0);
		cmd = cmd->next;
		while(wait(NULL) != -1)
			;
	return (status);
}



int phandle(int status)
{
    int new = WTERMSIG(status);
    if (new == SIGSEGV)
		printf("Minishell : %s\n", "Segmentation fault");
    if (new == SIGQUIT)
		printf("Quit\n");
    if (new == SIGINT)
		printf("interrupt\n");
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
	if(statu == 0 && !cmd->splitdata)
			return ;
	if (statu != -1)
		ft_exit_status(statu);
}
