/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_go_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:11:26 by azarda            #+#    #+#             */
/*   Updated: 2023/06/19 15:26:45 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int ft_execut_cmd(splitnode *cmd, t_env *env)
{
	if (ft_lstsize((t_env *)cmd) == 1)
	{
		if(ft_execut_bultins(cmd, env))
			return 1;
		ft_exec(cmd , env);
		return (1);
	}
	else
		printf("asbr azabi \n");
	return 0;
}
