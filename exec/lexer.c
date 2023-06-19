/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 02:31:29 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/06/06 01:02:08 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"


int	all_spaces(char *line)
{
	int i;
	int j;

	j = strlen(line);
	i = 0;
	while(*line)
	{
		if(*line != ' ')
			break;
		i++;
		line++;
	}
	if(i == j)
		return 1;
	return 0;

}
int	lexer(char *line)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if(*line == '|')
		return (0);
	while(*line)
	{
		if(*line == '\"')
			i++;
		else if(*line == '\'')
			j++;
		else if (*line == '|')
		{
			if( !*(line + 1) || *(line + 1) == '|')
				return (0);
			else if (*(line + 1) == ' ')
			{
				while(*(++line) == ' ')
				{
					if (!*(line + 1) || *(line + 1) == '|')
						return (0);
				}
				continue ;
			}
		}
		line++;
	}
	if (i % 2 != 0 || j % 2 != 0)
		return (0);
	return (1);
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
