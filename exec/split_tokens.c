/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 03:39:36 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/19 05:30:11 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	count_words(char *str, t_quote cq)
{
	while (cq.i < cq.length)
	{
		if (is_isspace(str[cq.i]) && !cq.in_word && (!cq.ins || !cq.ind))
		{
			cq.i++;
			continue ;
		}
		if ((str[cq.i] == '"' && !cq.ins) || (str[cq.i] == '\'' && !cq.ind))
			cq = check_quotes(cq, cq.i, str);
		else if (is_isspace(str[cq.i]) && (!cq.ins && !cq.ind))
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
	char	*array;

	array = (char *)ft_calloc((cq.i - cq.start + 1), sizeof(char));
	if (!array)
		return (NULL);
	ft_strncpy(array, &str[cq.start], cq.i - cq.start);
	return (array);
}

char	**split_string_loop(t_quote cq, char *str, char **words)
{
	while (cq.i <= cq.length && cq.word_index < cq.count)
	{
		if ((is_isspace(str[cq.i]) || str[cq.i] == '\0') && (!cq.ins && !cq.ind))
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
	words = (char **)ft_calloc((cq.count + 1), sizeof(char *));
	if (!words)
		return (NULL);
	while (cq.i < cq.length && is_isspace(str[cq.i]))
		cq.i++;
	cq.start = cq.i;
	words = split_string_loop(cq, str, words);
	return (words);
}

char	*ft_strndup(char *s1, int len)
{
	char	*sr;
	int		i;

	i = 0;
	sr = NULL;
	if (s1 && len)
	{
		sr = malloc((len + 1));
		if (!sr)
			return (NULL);
		while (s1[i] && len--)
		{
			sr[i] = s1[i];
			i++;
		}
		sr[i] = '\0';
	}
	return (sr);
}
