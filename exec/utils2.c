/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   white_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 21:14:33 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/05/25 00:10:14 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"


// size_t	ft_strlen(const	char *s)
// {
// 	const char	*c;

// 	c = s;
// 	while (*c)
// 		c++;
// 	return ((size_t)(c - s));
// }

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

// char	*ft_strdup( char *s1)
// {
// 	size_t	len;
// 	char	*dupl;
// 	char	*assl;
// 	size_t	i;

// 	len = ft_strlen(s1);
// 	assl = (char *)s1;
// 	i = 0;
// 	dupl = (char *)malloc(sizeof(*s1) * (len + 1));
// 	if (!dupl)
// 		return (NULL);
// 	while (i < len)
// 	{
// 		dupl[i] = assl[i];
// 		i++;
// 	}
// 	dupl[i] = '\0';
// 	return (dupl);
// }

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
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

// char	*ft_substr(char *s, unsigned int start, size_t len)
// {
// 	char	*sub;

// 	if (!s)
// 		return (NULL);
// 	if (start >= ft_strlen(s))
// 		start = ft_strlen(s);
// 	if (ft_strlen(s + start) < len)
// 		len = ft_strlen(s + start);
// 	sub = (char *)malloc(sizeof(*s) * (len + 1));
// 	if (!sub)
// 		return (NULL);
// 	ft_strlcpy(sub, s + start, len + 1);
//     free(s);
// 	return (sub);
// }

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


char    *ft_strcat(char *destination, const char    *source)
 {
    char    *result = NULL;
    int i = -1;
    int j = -1;
    // Move the pointer to the end of the destination string
    result = malloc(strlen(destination) + strlen(source) + 1);
    while (destination[++i] != '\0')
        result[i] = destination[i];

    // Copy the characters from the source string to the destination
    while (source[++j] != '\0')
        result[i++] = source[j];
    // Append a null character at the end of the concatenated string
    result[i] = '\0';

    return result;
}

