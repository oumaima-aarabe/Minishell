/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 21:14:43 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/05/23 21:14:44 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int which_quotes(char *array) 
{
    if (array[0] == '\'')
        return 1;
    else if (array[0] == '\"')
        return 2;
    return 0;
}

void checkquotes(splitnode *list)
{
    splitnode *current = list;

    while (current != NULL) 
    {
        char **splitdata = current->splitdata;

        int i = 0;
        while (splitdata[i] != NULL) 
        {
            int quoteType = which_quotes(splitdata[i]);

            if (quoteType == 1) 
            {
                splitdata[i] = ft_strtrim(splitdata[i], "\'");
            }
            else if (quoteType == 2)
            {
                splitdata[i] = ft_strtrim(splitdata[i], "\"");
            }
            i++;
        }

        current = current->next;
    }
}

