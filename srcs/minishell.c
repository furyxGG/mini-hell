/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyagbasa <fyagbasa@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 18:36:09 by fyagbasa          #+#    #+#             */
/*   Updated: 2025/12/28 21:03:09 by fyagbasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	minishell()
{
	char *line;
	
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("mini-hell >> ");
		if (line == NULL)
		{
			printf("exit\n");
			rl_clear_history();
			break;
		}
		if (*line)
        	add_history(line);
		printf("Girdi: %s\n", line);
		free(line);
	}
}