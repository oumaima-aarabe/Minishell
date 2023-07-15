/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 02:31:29 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/15 11:09:30 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	valid_quotes(char *line)
{
	int d;
	int s;

	d = 0;
	s = 0;
	t_quote cq;

	ft_memset(&cq, 0, sizeof(t_quote));
	while(*line)
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
	t_quote cq;

	ft_memset(&cq, 0, sizeof(t_quote));
	if (*line == ' ')
        while (*line == ' ')
            line++;
	if(*line == '|')
		return (0);
	while (*line)
	{
		cq = check_quotes(cq, 0, line);
		if (*line == '|' && !cq.in_dquotes && !cq.in_squotes)
		{
			if (!*(line + 1) || *(line + 1) == '|')
				return (0);
			else if (*(line + 1) == ' ')
			{
				while (*(++line) == ' ')
				{
					if (!*(line + 1) || *(line + 1) == '|')
						return (0);
				}
				continue ;
			}
		}
		line++;
	}
	return (1);
}

int		check_red1(char *line)
{
	t_quote cq;

	ft_memset(&cq, 0, sizeof(t_quote));
	while (*line)
	{
		cq = check_quotes(cq, 0, line);
		if (*line == '>' && !cq.in_dquotes && !cq.in_squotes)
		{
			if(*( line + 1 ) == '>')
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
		else if (*line == '<' && !cq.in_dquotes && !cq.in_squotes)
		{
			if(*( line + 1 ) == '<')
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
