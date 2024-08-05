/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 02:38:46 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/19 06:08:26 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	ft_dstrlen(char **dstr)
{
	int	i;

	i = 0;
	if (!dstr)
		return (i);
	while (dstr[i])
		i++;
	return (i);
}

char	**ft_joindstrs_at(char **ds1, char **ds2, int at)
{
	char	**words;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	words = ft_calloc(sizeof(char *), (ft_dstrlen(ds1) + ft_dstrlen(ds2)) + 1);
	if (!words)
		return (NULL);
	while (ds1[i] && i != at)
		words[k++] = ds1[i++];
	free (ds1[i]);
	while (ds2[j])
		words[k++] = ds2[j++];
	while (ds1[++i])
		words[k++] = ds1[i];
	free(ds1);
	free(ds2);
	return (words);
}

int	is_out_red(char *str)
{
	return (*str == '>' && *(str + 1) != '>');
}

int	is_isspace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

void	is_str(char *str, int *i)
{
	if (*str)
		(*i)++;
}
