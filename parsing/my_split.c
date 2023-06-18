/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 00:14:54 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/05/25 00:15:47 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	subs_count(char const *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			words++;
			while (s[i] != c && s[i] != '\0')
			{
				i++;
			}
			if (s[i] == '\0')
				return (words);
		}
		i++;
	}
	return (words);
}

static char	**ferfer(char **strarr)
{
	int	i;

	i = 0;
	while (strarr[i])
	{
		free(strarr[i]);
		i++;
	}
	free(strarr);
	return (NULL);
}

static int	word_end(char *s, char c, int i)
{
	int		trig;

	trig = 0;
	while (s != NULL && s[i] != '\0' && trig != 1)
	{
		if (s[i] != c)
		{
			while (s[i] != c && s[i] != '\0')
				i++;
			trig = 1;
		}
		if (trig != 1)
			i++;
	}
	return (i);
}

static char	*allo(char *s, char c, int i, int j)
{
	char	*word;
	int		trig;

	trig = 0;
	while (s && *s && trig != 1)
	{
		if (*s != c)
		{
			while (s[i] != c && s[i] != '\0')
				i++;
			trig = 1;
		}
		if (trig != 1)
			s++;
	}
	word = malloc(i + 1);
	if (!word)
		return (NULL);
	while (s && *s && *s != c)
	{
		word[j] = *s++;
		j++;
	}
	word[j] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**strarr;
	int		j;
	int		i;
	int		remember;

	if (!s)
		return (NULL);
	j = subs_count(s, c);
	i = -1;
	remember = 0;
	strarr = malloc(sizeof(char *) * (j + 1));
	if (!strarr)
		return (NULL);
	strarr[j] = NULL;
	while (++i < j)
	{
		strarr[i] = allo((char *)(s + remember), c, 0, 0);
		if (!strarr[i])
		{
			ferfer(strarr);
			return (NULL);
		}
		remember = word_end((char *)s, c, remember);
	}
	return (strarr);
}