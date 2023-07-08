/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_go_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:11:26 by azarda            #+#    #+#             */
/*   Updated: 2023/07/08 15:42:39 by azarda           ###   ########.fr       */
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
	int fd_in = dup(0);
	int fd_out = dup(1);

	if(cmd->in != -1)
	{
		dup2(cmd->in, 0);
		close(cmd->in);
	}
	if(cmd->out != -1)
	{
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

	if(ptr->in != -1)
		pipe.in = ptr->in;
	if(ptr->out != -1)
		pipe.out = ptr->out;

	pid = fork();
	if(pid == -1)
		return(perror("Minishell "), -1);
	if(pid == 0)
	{
		if (pipe.in != -1)
		{
			dup2(pipe.in, 0);
			close(pipe.in);
		}
		if (pipe.out != 1) //ila kan -1
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
	// int in_tmp = dup(0);
	// int out_tmp = dup(1);
	int fd[2];
	int dexieme_fd[2];
	int pid = 0;
	int status;

	// printf("one  -->> %c\n", cmd->splitdata[0][0]);
	if(!cmd->splitdata[0])
		return (-1);

	if(!cmd->next)
		return (ft_one_cmd(cmd, g_v.env)); // ft_one_cd return -1 if execut bulti



	// if (cmd->next)
	// {
		pipe(fd);
		// printf("-- >> >> %s\n", cmd->splitdata[0]);
		pid =  fork_execut(cmd, (t_fds){cmd->in, fd[1], fd[0], -1}, g_v.env);
		// puts("wra lwl ");

		close(fd[1]);
		if(cmd->next)
			cmd = cmd->next;
		while(cmd)
		{
			// puts(" chi 7aja");
			pipe(dexieme_fd);
			// printf("-- >> >> %s\n", cmd->splitdata[0]);
			pid =  fork_execut(cmd, (t_fds){fd[0], dexieme_fd[1], dexieme_fd[0], -1}, g_v.env);
			if(pid == -1)
				return (-1);
			close(fd[0]);
			fd[0] = dexieme_fd[0];
			close(dexieme_fd[1]);
			if (cmd->next == NULL)
				break;
			cmd = cmd->next;
		}
		// cmd = cmd->next;
			// printf("-- >> wra while %s\n", cmd->splitdata[0]);

		// pid = fork_execut(cmd, (t_fds){fd[0], cmd->out, -1, -1}, g_v.env);
		close(fd[0]);
		waitpid(pid, &status, 0);
		while(wait(NULL) != -1)
			;
	return (status);
	// }
	return (-1); //
}



int phandle(int status)
{
    int new = WTERMSIG(status);
    if (new == SIGSEGV)
	{
        ft_putstr_fd("ha wahd  segv ", 2);
		puts("  ok");
	}

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
			// printf("-->> %s\n",cmd->splitdata[0]);

	statu = ft_execut_cmd(cmd);
	// printf("%d\n", statu);
		// if(statu == 0)
		// {
		// 	return ;
		// }
	if (statu != -1)
		ft_exit_status(statu);
	// printf("%d\n", g_v.ex_s);
}
