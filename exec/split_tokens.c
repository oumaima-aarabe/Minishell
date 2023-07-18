/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 03:39:36 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/18 12:27:39 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	count_words(char *str, t_quote cq)
{
	while (cq.i < cq.length)
	{
		if ((str[cq.i] == ' ' || str[cq.i] == '\t') && \
		!cq.in_word && (!cq.ins || !cq.ind))
		{
			cq.i++;
			continue ;
		}
		if ((str[cq.i] == '"' && !cq.ins) || \
		(str[cq.i] == '\'' && !cq.ind))
			cq = check_quotes(cq, cq.i, str);
		else if ((str[cq.i] == ' ' || str[cq.i] == '\t') && \
		(!cq.ins && !cq.ind))
		{
			cq.in_word = 0;
			cq.count++;
		}
		else
			cq.in_word = 1;
		cq.i++;
	}
	if (cq.in_word)
		cq.count++;
	return (cq.count);
}

char	*fill_array(char *str, t_quote cq)
{
	char *array;

	array = (char *)ft_calloc((cq.i - cq.start + 1) , sizeof(char)); // ! ha wa7d calloc
	if (!array)
		return (NULL);
	strncpy(array, &str[cq.start], cq.i - cq.start); // ! strncpy
	return (array);
}

char	**split_string_loop(t_quote cq, char *str, char **words)
{
	while (cq.i <= cq.length && cq.word_index < cq.count)
	{
		if ((str[cq.i] == ' ' || str[cq.i] == '\t' || \
		str[cq.i] == '\0') && (!cq.ins && !cq.ind))
		{
			if (cq.in_word)
			{
				words[cq.word_index] = fill_array(str, cq);
				cq.word_index++;
				cq.in_word = 0;
			}
			cq.start = cq.i + 1;
		}
		else if ((str[cq.i] == '"' && !cq.ins) || \
		(str[cq.i] == '\'' && !cq.ind))
			cq = check_quotes(cq, cq.i, str);
		else
			cq.in_word = 1;
		cq.i++;
	}
	return (words);
}

char	**split_string(char *str, t_quote cq)
{
	char	**words;

	cq.count = count_words(str, cq);
	words = (char **)calloc((cq.count + 1) , sizeof(char *)); // ! calloc
	if (!words)
		return (NULL);
	while (cq.i < cq.length && (str[cq.i] == ' ' || str[cq.i] == '\t'))
		cq.i++;
	cq.start = cq.i;
	words = split_string_loop(cq, str, words);
	return (words);
}
