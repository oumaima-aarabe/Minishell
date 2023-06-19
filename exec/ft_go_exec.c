/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_go_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:11:26 by azarda            #+#    #+#             */
/*   Updated: 2023/06/19 20:38:53 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int ft_execut_cmd(splitnode *cmd, t_env *env)
{
	// int i = 0;

	// while(cmd && cmd->next)
	// {
	// 	while(cmd->splitdata[i])
	// 	printf("cmd -->%s\n", cmd->splitdata[i++]);
	// 	// printf("in --> %d\n", cmd->in);
	// 	// printf("out --> %d\n", cmd->out);
	// 	cmd = cmd->next;
	// 	i = 0;
	// }
	// (ft_lstsize((t_env *)cmd) == 1)
	// {
		if(ft_execut_bultins(cmd, env))
			return 1;
		ft_exec(cmd , env);
		return (1);
	// }
	return 0;
}
