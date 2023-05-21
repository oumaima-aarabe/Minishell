/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 22:33:55 by azarda            #+#    #+#             */
/*   Updated: 2023/05/21 15:45:52 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"
# include <unistd.h>


int main(int ac , char **av, char **env)
{
    char *str[] = {"ls",  NULL};
    execve("/usr/bin/whereis", str, env);
    exit (0);
    perror(av[1]);
}

