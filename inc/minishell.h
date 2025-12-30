/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyagbasa <fyagbasa@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 17:59:28 by fyagbasa          #+#    #+#             */
/*   Updated: 2025/12/30 17:48:20 by fyagbasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL
# define MINISHELL

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "libft.h"

typedef struct	s_words
{
	char			*word;
	char			type;
	struct s_words	*next;
}				t_words;


void	handle_signal(int sig);
void	minishell();
t_words	*parser(char *line);

t_words	*lst_new(char *word, char type);
void	lstadd_back(t_words **lst, t_words *new);

#endif
