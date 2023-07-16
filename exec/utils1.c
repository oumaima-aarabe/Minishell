/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 21:14:30 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/15 04:59:43 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}
int	ft_isnum(int c)
{
	return ((c >= '9' && c <= '9'));
}

int	ft_isalnum(int c)
{
	return(ft_isalpha(c) || ft_isnum(c));
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

int	ft_atoi(char *str)
{
	int		s;
	long	d;

	s = 1;
	d = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			s *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (d > d * 10 + *str - '0' && s == -1)
			return (0);
		if (d > d * 10 + *str - '0' && s == 1)
			return (-1);
		d = d * 10 + *str - '0';
			str++;
	}
	return ((int)(d * s));
}
