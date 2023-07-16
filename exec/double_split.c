/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 02:38:46 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/07/16 03:25:14 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int ft_double_strlen(char **dstr)
{
    int i;

    i = 0;
    if (!dstr)
        return (i);
    while (dstr[i])
        i++;
    return (i);
}

char    **ft_joindstrs_at(char **ds1, char **ds2, int at)
{
    char    **words;
    int     i;
    int     j;
    int     k;  

    i = 0;
    j = 0;
    k = 0;
        
    words = calloc(sizeof(char *) , \
    (ft_double_strlen(ds1) + ft_double_strlen(ds2)) + 1);
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
