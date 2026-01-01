/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyagbasa <fyagbasa@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 18:36:09 by fyagbasa          #+#    #+#             */
/*   Updated: 2026/01/01 19:18:59 by fyagbasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void print_list(t_words *head)
{
    t_words *tmp;

    if (!head)
    {
        printf("(Liste Bos)\n");
        return ;
    }
    tmp = head;
    while (tmp)
    {
        printf("Token: [%-15s] | Type: [%c]\n", tmp->word, tmp->type);
        tmp = tmp->next;
    }
    printf("--- Listenin Sonu ---\n");
}

void	minishell()
{
	char	*line;
	t_words *words;
	
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	g_status_code = 0;
	words = NULL;
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
		{
        	add_history(line);
			words = parser(line);
			expansion(words);
			divide_pipe(words);
		}
		print_list(words);
		free(line);
		free_words_list(words);
	}
	(void)words;
}