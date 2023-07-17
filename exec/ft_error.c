/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 02:18:13 by azarda            #+#    #+#             */
/*   Updated: 2023/07/17 09:27:32 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	ft_syntax_err(void)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putendl_fd("syntax error", 2);
	g_v.ex_s = 258;
}

void	ft_print_err(char *cmd, char *st)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(st, 2);
}
