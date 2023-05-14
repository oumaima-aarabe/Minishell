/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:19:44 by azarda            #+#    #+#             */
/*   Updated: 2023/05/14 02:14:45 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void  ctr_c(int sig)
{
    (void)sig;
    printf("\n");
    rl_on_new_line();
    rl_replace_line(" ", 0);
	rl_redisplay();
		
}


int main(int ac, char **av, char  **env)
{
    (void)av;
    (void)env;
    if(ac != 1)
    {
        printf("Minishell do not take any arguments  \n");
        exit(1);
    }
    char *str;
    while(1337)
    {
        signal(SIGQUIT, SIG_IGN);
        signal(SIGINT,  ctr_c);
        str = readline("  -> ");
        if(!str)
        {
            printf("exit\n");
            exit(0);
        }
        printf("%s\n", str);
    }
}