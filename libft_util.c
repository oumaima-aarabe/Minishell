/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 21:42:52 by azarda            #+#    #+#             */
/*   Updated: 2023/06/09 22:26:08 by azarda           ###   ########.fr       */
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


int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
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

char	*ft_substr(char const *s,  int start, int len)
{
	int	i;
	int	j;
	char	*str;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
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

int ft_strlen(char const *str)
{
	int i = 0;
	while(str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*tab;
	int		len_s1;
	int		len_s2;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	tab = (char *)malloc(sizeof(char) * ((len_s1 + len_s2) + 1));
	if (!tab)
		return (NULL);
	while (s1[i])
	{
		tab[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		tab[i++] = s2[j++];
	}
	free(s1);
	free(s2);
	return (tab[i] = '\0', tab);
}


static	int	ft_calcul(const char *s, char d)
{
	int	i;
	int	cont;

	if (s[0] != d)
		cont = 1;
	else
		cont = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] && s[i] == d && s[i + 1] != d && s[i + 1] != '\0')
			cont++;
		i++;
	}
	return (cont);
}

void	ft_free_(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

static	char	**ft_my_split(char const *str, char d, int i, int j)
{
	char	**tab;
	int		debut;
	int		fin;

	if (!str)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (ft_calcul(str, d) + 1));
	if (!tab)
		return (NULL);
	while (str[i] != '\0')
	{
		while (str[i] && str[i] == d)
			i++;
		debut = i;
		while (str[i] && str[i] != d)
			i++;
		fin = i;
		if (j < ft_calcul(str, d))
		{
			tab[j++] = ft_substr(str, debut, fin - debut);
			if (!tab[j - 1])
				return (ft_free_(tab), NULL);
		}
	}
	return (tab[j] = NULL, tab);
}

char	**ft_split(char  *st, char c)
{
	char	**tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if(!st)
		return (NULL);
	tab = ft_my_split(st, c, i, j);
	return (tab);
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

