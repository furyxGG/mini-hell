/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyagbasa <fyagbasa@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 19:51:51 by fyagbasa          #+#    #+#             */
/*   Updated: 2026/01/01 22:05:14 by fyagbasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_count(t_words *words)
{
	t_words *tmp;
	int		a;

	tmp = words;
	a = 0;
	while (tmp)
	{
		if (tmp->type == 'p')
			a++;
		tmp = tmp->next;
	}
	return (a);
}

int	arg_count(t_words *words)
{
	int		a;
	t_words	*tmp;

	tmp = words;
	a = 0;
	while (tmp)
	{
		if (ft_strchr("qQw", tmp->type))
			a++;
		if (tmp->type == 'p')
			break ;
		if (tmp->type == 'o' && tmp->next)
		{
			tmp = tmp->next->next;
			continue ;
		}
		tmp = tmp->next;
	}
	return (a);
}