/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 04:20:51 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/12 04:31:05 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

char	*quotes_removed(int count, char *input)
{
	char	*output;
	int		j;
	int		i;
	t_quote	check_q;

	output = calloc(count + 1, sizeof(char));
	j = 0;
	i = 0;
	check_q = init_q();
	while (i < ft_strlen(input))
	{
		check_q = check_quotes(check_q, i, input);
		if (!check_q.changed)
			output[j++] = input[i];
		i++;
	}
	free (input);
	return (output);
}

char	*removequotes(char *input)
{
	int		count;
	t_quote	check_q;
	int		i;

	if (input)
	{
		count = 0;
		check_q = init_q();
		i = 0;
		while (i < ft_strlen(input))
		{
			check_q = check_quotes(check_q, i, input);
			if (!check_q.changed)
				count++;
			i++;
		}
		return (quotes_removed(count, input));
	}
	return (input);
}
