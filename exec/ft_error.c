/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 02:18:13 by azarda            #+#    #+#             */
/*   Updated: 2023/07/17 05:03:35 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	ft_syntax_err(void)
{
	ft_putstr_fd("Minishell ", 2);
	ft_putendl_fd("syntax error", 2);
}

void	ft_print_err(char *cmd, char *st)
{
	ft_putstr_fd("Minishell ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(st, 2);
}
