/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 02:31:29 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/19 05:00:25 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	valid_quotes(char *line)
{
	int		d;
	int		s;
	t_quote	cq;

	d = 0;
	s = 0;
	ft_memset(&cq, 0, sizeof(t_quote));
	while (*line)
	{
		cq = check_quotes(cq, 0, line);
		if (cq.changed == 2)
			d++;
		else if (cq.changed == 1)
			s++;
		line++;
	}
	return (s % 2 == 0 && d % 2 == 0);
}

int	check_pipe(char *line)
{
	t_quote	cq;

	ft_memset(&cq, 0, sizeof(t_quote));
	while (*line == ' ')
		line++;
	if (*line == '|')
		return (0);
	while (*line)
	{
		cq = check_quotes(cq, 0, line);
		if (*line == '|' && !cq.ind && !cq.ins)
		{
			if (!*(line + 1) || *(line + 1) == '|')
				return (0);
			else if (*(line + 1) == ' ')
			{
				while (*(++line) == ' ')
					if (!*(line + 1) || *(line + 1) == '|')
						return (0);
				continue ;
			}
		}
		line++;
	}
	return (1);
}

int	check_red1(char *line)
{
	t_quote	cq;

	ft_memset(&cq, 0, sizeof(t_quote));
	while (*line)
	{
		cq = check_quotes(cq, 0, line);
		if (*line == '>' && !cq.ind && !cq.ins)
		{
			if (*(line + 1) == '>')
				line += 2;
			else
				line++;
			while (*line == ' ')
				line++;
			if (*line == '\0')
				return (0);
			if (*line == '<' || *line == '>' || *line == '|' )
				return (0);
		}
		line++;
	}
	return (1);
}

int	check_red2(char *line)
{
	t_quote	cq;

	ft_memset(&cq, 0, sizeof(t_quote));
	while (*line)
	{
		cq = check_quotes(cq, 0, line);
		if (*line == '<' && !cq.ind && !cq.ins)
		{
			if (*(line + 1) == '<')
				line += 2;
			else
				line++;
			while (*line == ' ')
				line++;
			if (*line == '\0')
				return (0);
			if (*line == '<' || *line == '>' || *line == '|' )
				return (0);
		}
		line++;
	}
	return (1);
}

int	valid_syntax(char *prompt)
{
	t_splitnode	*tokens;

	tokens = NULL;
	add_history(prompt);
	if (!valid_quotes(prompt) || !check_pipe(prompt) || \
	!check_red1(prompt) || !check_red2(prompt))
	{
		free(prompt);
		ft_syntax_err();
		return (0);
	}
	tokens = parsing(prompt, g_v.env);
	execution(tokens);
	ft_pwd();
	free_split_nodes(tokens);
	return (1);
}
