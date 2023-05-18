/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 22:33:55 by azarda            #+#    #+#             */
/*   Updated: 2023/05/18 01:49:07 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"
# include <unistd.h>


int main(int ac , char **av)
{
    // char *str[] = {"/bin/ls", NULL};
    // char *str2[] = {NULL};
    // execve("/bin/ls", str, str2);   
    // exit (0);
    perror(av[1]);
}