/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_go_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:11:26 by azarda            #+#    #+#             */
/*   Updated: 2023/06/25 01:22:42 by azarda           ###   ########.fr       */
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

typedef struct s_fds
{
	int in;
	int out;
	int fd_in;
	int fd_out;
}	t_fds;

int fork_execut(splitnode *ptr, t_fds pipe, t_env *env)
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

int ft_one_cmd(splitnode *cmd, t_env *env)
{
	int pid;
	pid = 0;
	if(ft_execut_bultins(cmd->splitdata))
		return (-1);
	pid = fork();
	if(pid == -1)
		return(perror("Minishell: "), -1);
	if(pid == 0)
		ft_exec(cmd->splitdata , env);
	return (pid);
}


int ft_execut_cmd(splitnode *cmd)
{
	int fd[2];
	int dexieme_fd[2];
	int pid = 0;
	int status;

	if(!cmd->next)
	{
		pid = ft_one_cmd(cmd, g_v.env);
		if (pid == -1)
			return(-1);
		return (waitpid(pid, &status, 0), status);
	}
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
	return (0x5ABA); //
}



int phandle(int status)
{
    int new = WTERMSIG(status);

    if (new == SIGINT)
        printf("Minishell : SIG : %s\n", "interrupt");

    return (WTERMSIG(status) + 128);
}



int ft_exit_status(int	statu)
{
	// (void)statu;
	if (WIFEXITED(statu))
        return (g_v.ex_s = (WTERMSIG(statu)), 1);
	else if (WIFSIGNALED(statu))
        return (phandle(statu));
	return (0);
}

void execution(splitnode *cmd)
{
	int statu;

	statu = ft_execut_cmd(cmd);
	// 	// if(statu == -1)
	// 	// {

	// 	// 	return ;
	// 	// }
	// 	// if (statu != 0x5ABA)
	ft_exit_status(statu);

}






	// pid =  fork_execut(cmd, 0, 1, env);
	// dup2(fd[0], 0);
	// char buf[100];
	// read(0, buf, 100);
	// printf("->%s\n", buf);
//_________________________________________________________________________________________________________
//_________________________________________________________________________________________________________






	// if (cmd && cmd->next)
	// {
	// 	while(cmd && cmd->next)
	// 	{
	// 		pipe(fd);
	// 		if (cmd->out == -1)
	// 			cmd->out = fd[1];
	// 		if (cmd->in == -1)
	// 			cmd->in = fd[0];
	// 		if (i)
	// 			cmd->in = cmd->prev->in;
	// 		// ft_execut_bultins(cmd, env);
	// 		if(ft_execut_bultins(cmd, env))
	// 		{
	// 			cmd = cmd->next;
	// 			continue;
	// 		}
	// 		else
	// 			ft_exec(cmd , env);
	// 		close(fd[1]);
	// 		if (i)
	// 			close(cmd->in);
	// 		cmd = cmd->next;

	// 		i = !i;

	// 	}
	// 	if(ft_execut_bultins(cmd, env))
	// 		;
	// 	else
	// 		ft_exec(cmd , env);
	// 	close(fd[0]);
	// }
//---------------------------------------------------------------------------------------------------
	// int fd[2];
	// if (cmd->out == -1)
	// 	cmd->out = fd[1];
	// if (cmd->in == -1)
	// 	cmd->in = fd[0];


	// unsigned int i = 0;
	// int id;
	// if(cmd && cmd->next)
	// {
	// 	while (cmd->next)
	// 	{
	// 	pipe(fd);
	// 	id = fork();
	// 	// if(!i)
	// 	// 	close(fd[0]);
	// 	if(ft_execut_bultins(cmd, env))
	// 	{

	// 		exit(0);
	// 		cmd = cmd->next;
	// 		continue;
	// 	}
	// 	ft_exec(cmd , env);
	// 		cmd = cmd->next;
	// 	}
		// if(ft_execut_bultins(cmd, env))
		// 	return 1;
		// ft_exec(cmd , env);
		// return (1);
		// // wait(&id);

	// }
	// else
	// {
