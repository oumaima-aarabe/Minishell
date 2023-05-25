/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouaarabe <ouaarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 00:49:01 by ouaarabe          #+#    #+#             */
/*   Updated: 2023/05/23 00:50:51 by ouaarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "minishell.h"

 int main()
 {
    // Initialize the shell state
    struct ShellState state;
    state.history_head = NULL;
    state.history_tail = NULL;

    // Set up signal handlers
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, sigquit_handler);

    // Start executing commands
    execute_commands(&state);

    return 0;
}
