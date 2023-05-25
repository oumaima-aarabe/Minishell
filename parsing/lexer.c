/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 02:31:29 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/05/25 00:08:32 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexer(char *line)
{
	char	*tmp;
	size_t	len;
	size_t	i;
	size_t	j;

	tmp = line;	
	if (!line || !(*line))
		return (0);
	len = strlen(line);
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
