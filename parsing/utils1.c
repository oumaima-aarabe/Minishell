/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 21:14:30 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/03 05:42:51 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*s;

	s = (unsigned char *)b;
	while (len--)
	{
		*s = (unsigned char)c;
		s++;
	}
	return (b);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	len;

	if (count == 0 || size == 0)
		len = 0;
	else if (count >= (SIZE_MAX / size) || size >= (SIZE_MAX / count))
		len = SIZE_MAX;
	else
		len = size * count;
	ptr = malloc(len);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, len);
	return (ptr);
}

// void	*ft_realloc(void *ptr, size_t newsize)
// {
// 	void	*newptr;
// 	size_t	cursize;

// 	if (ptr == NULL)
// 		return (ft_calloc(1, newsize));
// 			// Use calloc to allocate and initialize the memory
// 	cursize =  ft_strlen(ptr);
// 	if (newsize <= cursize)
// 		return (ptr);
// 	newptr = ft_calloc(1, newsize);
// 		// Use calloc to allocate and initialize the new memory block
// 	memcpy(newptr, ptr, cursize);
// 	free(ptr);
// 	return (newptr);
// }