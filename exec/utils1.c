/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 21:14:30 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/05/25 00:31:59 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	char	*tab;
// 	int		len_s1;
// 	int		len_s2;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	if (!s1 || !s2)
// 		return (NULL);
// 	len_s1 = strlen(s1);
// 	len_s2 = strlen(s2);
// 	tab = (char *)malloc(sizeof(char) * ((len_s1 + len_s2) + 1));
// 	if (!tab)
// 		return (NULL);
// 	while (s1[i])
// 	{
// 		tab[i] = s1[i];
// 		i++;
// 	}
// 	while (s2[j])
// 	{
// 		tab[i++] = s2[j++];
// 	}
// 	free(s1);
// 	s1 = NULL;
// 	return (tab[i] = '\0', tab);
// }

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}
// int	ft_isdigit(int c)
// {
// 	return (c >= '0' && c <= '9');
// }

// int	ft_isalnum(int c)
// {
// 	return (ft_isalpha(c) || ft_isdigit(c));
// }

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

// size_t malloc_usable_size(void *ptr) {
//     if (ptr == NULL)
//         return 0;

//     void *header_ptr = ptr - sizeof(size_t);
//     size_t block_size;
//     memcpy(&block_size, header_ptr, sizeof(size_t));
//     return block_size - sizeof(size_t);
// }

// void *my_realloc(void *ptr, size_t new_size) {
//     if (new_size == 0) {
//         free(ptr);
//         return NULL;
//     }

//     if (ptr == NULL)
//         return malloc(new_size);

//     size_t old_size = malloc_usable_size(ptr);
//     if (old_size < new_size) {
//         void *new_ptr = malloc(new_size);
//         if (new_ptr == NULL)
//             return NULL;

//         memcpy(new_ptr, ptr, old_size);
//         free(ptr);
//         return new_ptr;
//     } else {
//         return ptr;
//     }
// }

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
