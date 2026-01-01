/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyagbasa <fyagbasa@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 17:59:28 by fyagbasa          #+#    #+#             */
/*   Updated: 2026/01/01 22:33:00 by fyagbasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL
# define MINISHELL

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "libft.h"

extern int g_status_code;
typedef struct	s_words
{
	char			*word;
	char			type;
	int				space_check;
	struct s_words	*next;
}				t_words;

typedef struct	s_cmd
{
	char			**args;
	char			*path;
	int				fd_in;
	int				fd_out;
	struct s_cmd	*next;
}				t_cmd;


void	handle_signal(int sig);
void	minishell();
t_words	*parser(char *line);

void	expansion(t_words *words);
char	*get_variable_name(t_words *word);
void	expansion_helper(t_words *words);
void	expansion_helper_null(t_words *words);
void	expansion_helper_s_code(t_words *words);

t_cmd	*divide_pipe(t_words *words);
int		pipe_count(t_words *words);
int		arg_count(t_words *words);

void	find_path(t_cmd *cmd, char	**envt);

t_words	*lst_new(char *word, char type, int space_check);
int		lst_count(t_words *words);
void	lstadd_back(t_words **lst, t_words *new);
char	*join_free(char *s1, char *s2);
void	free_words_list(t_words *words);

#endif
