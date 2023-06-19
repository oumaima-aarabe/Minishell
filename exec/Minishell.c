/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:19:44 by azarda            #+#    #+#             */
/*   Updated: 2023/06/18 03:25:15 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"




void ft_print_err(char *cmd, char *st)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(st, 2);
}



//________________________________________________________________________________

void le()
{
	system("leaks minishell");
}
//________________________________________________________________________________



//________________________________________________________________________________







// int main(int ac, char **av, char  **env)
// {
// 	(void)av;
// 	// char *pwd;
// 	char *str;
// 	char **cmd;


// 	t_env *en;

// 	// if(!env || !(*env))
// 	// 	exit(5);

// 	en = environment(env);


// 	if(ac != 1)
// 	{
// 		printf("minishell no take arguments\n"); // change msg
// 		exit(1);
// 	}

// 	// atexit(le);
// 	rl_catch_signals=0;
// 	while(1337)
// 	{
// 		signal(SIGQUIT, SIG_IGN);
// 		signal(SIGINT,  ctr_c);
// 		//pwd = ft_strjoin(getcwd(NULL, 0), " -> "); // 1bite leaks pwd

// 		str = readline("minishell $ ");
// 		// free(pwd);
// 		if(!str)
// 		{
// 			printf("exit\n");
// 			exit(0);
// 		}
// 		cmd = ft_split(str, ' ');
// 		cmd = ft_expend(cmd,en);
// 		add_history(str);
// 		free(str);
// 		str = NULL;
// 		if(ft_execut_bultins(cmd, en))
// 		{
// 			ft_free_(cmd);
// 			continue;
// 		}
// 			ft_exec(cmd, en);
// 			ft_free_(cmd);

// 	}
// }
