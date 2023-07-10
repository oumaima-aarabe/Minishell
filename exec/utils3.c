/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 08:40:44 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/10 12:32:08 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
		write(fd, &s[i++], 1);
}
void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
		write(fd, &s[i++], 1);
	write(fd, "\n", 1);
}

int	ft_strncmp( char *s1,  char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	if(ft_strlen(s1) != ft_strlen(s2))
		return (1);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
	i++;
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}

char	*ft_strdup(char *s1)
{
	char	*sr;
	int		i;

	i = 0;
	sr = malloc((ft_strlen(s1) + 1));
	if (!sr)
		return (NULL);
	while (s1[i])
	{
		sr[i] = s1[i];
		i++;
	}
	sr[i] = '\0';
	return (sr);
}

char	*ft_substr(char *s, int start, int len)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (NULL);
	if (len > ft_strlen(s) - start + 1)
		len = ft_strlen(s) - start + 1;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (s[i])
	{
		if (i >= start && j < len)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	return (str[j] = '\0', str);
}

int	ft_strcmp(char	*s1, char	*s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}
