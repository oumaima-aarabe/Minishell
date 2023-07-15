/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 21:14:33 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/15 11:20:25 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	ft_strlen(char *s)
{
	const char	*c;

	c = s;
	while (*c)
		c++;
	return ((size_t)(c - s));
}

char	*ft_strchr(char *s, int c)
{
	size_t	i;

	i = 0;
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}

size_t	ft_strlcpy(char *dest, char *src, size_t size)
{
	size_t	c;

	c = ft_strlen(src);
	if (size == 0)
		return (c);
	while (*src && --size)
	{
		*(dest++) = *(src++);
	}
		*dest = '\0';
	return (c);
}

char	*ft_strtrim(char *s1, char *set)
{
	size_t	i;
	size_t	j;
	size_t	len;

	if (!s1)
		return (NULL);
	if (!set || *set == '\0')
		return (ft_strdup(s1));
	i = 0;
	while (ft_strchr(set, s1[i]) && s1[i] != '\0')
		i++;
	j = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[j]) && j != 0 && j >= i)
		j--;
	len = j - i + 1;
	return (ft_substr(s1, i, len));
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*tab;
	t_hd	index;

	ft_memmset(&index, 0, sizeof(t_hd));
	if(!s1 && s2)
	{
		return (ft_strdup(s2));
	}
	if (!s1 || !s2)
		return (NULL);
	tab = (char *)calloc(sizeof(char) ,((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (!tab)
		return (NULL);
	while (s1[index.i])
	{
		tab[index.i] = s1[index.i];
		index.i++;
	}
	while (s2[index.j])
	{
		tab[index.i++] = s2[index.j++];
	}
	free(s1);
	free(s2);
	return  (tab);
}
