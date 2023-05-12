/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:19:44 by azarda            #+#    #+#             */
/*   Updated: 2023/05/12 18:36:24 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int main(int ac, char **av, char  **env)
{
    (void)av;
    (void)env;
    if(ac != 1)
    {
        printf("Minishell ma katakhod waloo al9lawi \n");
        exit(1);
    }
    char *str;
    while(1337)
    {
        str = readline("  -> ");
        if(!str)
        {
            printf("exit\n");
            exit(0);
        }
        printf("%s\n", str);
    }
}