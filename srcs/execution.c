/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyagbasa <fyagbasa@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 17:54:36 by fyagbasa          #+#    #+#             */
/*   Updated: 2026/01/01 22:10:28 by fyagbasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*new_cmds(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	cmd->args = NULL;
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->next = NULL;
	cmd->path = NULL;
	return (cmd);
}

static void	args_helper(t_words **tmp, t_cmd *temp_cmd)
{
	int	a;

	a = 0;
	while (*tmp)
	{
		if ((*tmp)->type == 'o' && ((*tmp)->word[0] == '>' || (*tmp)->word[0] == '<') && (*tmp)->word[1] == '\0')
		{
			if ((*tmp)->next)
			{
				if ((*tmp)->word[0] == '>')
				{
					if (temp_cmd->fd_out != 1)
						close(temp_cmd->fd_out);
					temp_cmd->fd_out = open((*tmp)->next->word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				}
				else
					temp_cmd->fd_in = open((*tmp)->next->word, O_RDONLY);
				*tmp = (*tmp)->next->next;
			}
		}
		else if ((*tmp)->type == 'p')
		{
			*tmp = (*tmp)->next;
			break ;
		}
		else
		{
			temp_cmd->args[a++] = ft_strdup((*tmp)->word);
			*tmp = (*tmp)->next;
		}
	}
	temp_cmd->args[a] = NULL;
}

static void	create_args(t_words *words, t_cmd *cmd)
{
	int		pipcount;
	t_words	*tmp;
	t_cmd	*temp_cmd;

	pipcount = pipe_count(words);
	temp_cmd = cmd;
	tmp = words;
	while (pipcount >= 0)
	{
		temp_cmd->args = (char **)malloc((arg_count(tmp) + 1) * sizeof(char *));
		args_helper(&tmp, temp_cmd);
		if (pipcount != 0)
			temp_cmd->next = new_cmds();
		else
			temp_cmd->next = NULL;
		temp_cmd = temp_cmd->next;
		pipcount--;
	}
}

void	divide_pipe(t_words *words)
{
	t_cmd	*cmd;
	int		a;

	cmd = new_cmds();
	create_args(words, cmd);
	printf("inputfd: %d\n", cmd->fd_in);
	printf("outputfd: %d\n", cmd->fd_out);
	while (cmd)
	{
		a = 0;
		while (cmd->args[a])
		{
			printf("\narg: %s", cmd->args[a]);
			a++;
		}
		cmd = cmd->next;
	}
}
