/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 04:20:51 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/14 03:57:08 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

t_quote	init_q(void)
{
	t_quote	check_q;

	check_q.in_dquotes = 0;
	check_q.in_squotes = 0;
	check_q.changed = 0;
	return (check_q);
}

t_quote	check_quotes(t_quote check_q, int j, char *cmd)
{
	if (cmd[j] == '\'' && !check_q.in_dquotes)
	{
		check_q.changed = 1;
		check_q.in_squotes = !check_q.in_squotes;
	}
	else if (cmd[j] == '"' && !check_q.in_squotes)
	{
		check_q.changed = 2;
		check_q.in_dquotes = !check_q.in_dquotes;
	}
	else 
        check_q.changed = 0;
	return (check_q);
}

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
