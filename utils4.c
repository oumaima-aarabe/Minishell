/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 06:04:12 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/18 15:33:09 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	ft_atoi_exit(char *str, int i)
{
	int		s;
	long	d;

	s = 1;
	d = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (d > d * 10 + str[i] - '0')
			return (ft_print_err(str, \
		" : numeric argument required\n"), exit(255), 1);
		d = d * 10 + str[i] - '0';
		i++;
	}
	if (str[i] != '\0')
		return (ft_print_err(str, \
		" : numeric argument required\n"), exit(255), 1);
	return ((int)(d * s));
}

int	compar(int a, int b)
{
	if (a > b)
		return (0);
	return (1);
}

char	*ft_strdup(char *s1)
{
	char	*sr;
	int		i;

	i = 0;
	sr = NULL;
	if (s1)
	{
		sr = malloc((ft_strlen(s1) + 1));
		if (!sr)
			return (NULL);
		while (s1[i])
		{
			sr[i] = s1[i];
			i++;
		}
		sr[i] = '\0';
	}
	return (sr);
}

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int	ft_isnum(int c)
{
	return ((c >= '0' && c <= '9'));
}
