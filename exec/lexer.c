/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 02:31:29 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/10 00:34:55 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	lexer(char *line)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (*line == '|')
		return (0);
	while (*line)
	{
		if (*line == '"')
			i++;
		else if (*line == '\'')
			j++;
		else if (*line == '|')
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
	return (i % 2 == 0 || j % 2 == 0);
}

int		lexer2(char *line)
{
	while (*line)
	{
		if (*line == '>')
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
		else if (*line == '<')
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
