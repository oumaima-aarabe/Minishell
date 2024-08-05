/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 21:42:52 by azarda            #+#    #+#             */
/*   Updated: 2023/07/03 09:53:15 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

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

static	char	**ft_my_split(char *str, char d, int i, int j)
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

char	**ft_split(char *st, char c)
{
	char	**tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!st)
		return (NULL);
	tab = ft_my_split(st, c, i, j);
	return (tab);
}

static int	ft_get_size(int n)
{
	int	c;

	c = 0;
	if (n < 0)
	{
		c++;
		n *= -1;
	}
	if (n == 0)
		c++;
	while (n != 0)
	{
		n = n / 10;
		c++;
	}
	return (c);
}

char	*ft_itoa(int n)
{
	char	*tab;
	int		size;
	long	nbr;

	nbr = n;
	size = ft_get_size(nbr);
	tab = (char *)malloc(sizeof(char) * (size + 1));
	if (!tab)
		return (NULL);
	tab[size--] = '\0';
	if (nbr < 0)
	{
		nbr *= -1;
		tab[0] = '-';
	}
	if (nbr == 0)
		tab[size] = '0';
	while (nbr != 0)
	{
		tab[size--] = nbr % 10 + '0';
		nbr = nbr / 10;
	}
	return (tab);
}
