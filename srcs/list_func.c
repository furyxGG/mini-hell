/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyagbasa <fyagbasa@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 16:49:12 by fyagbasa          #+#    #+#             */
/*   Updated: 2025/12/29 17:26:48 by fyagbasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_words	*lst_new(char *word, char type)
{
	t_words	*list;

	list = (t_words *)malloc(sizeof(t_words));
	if (!list)
		return (0);
	list->word = word;
	list->type = type;
	list->next = NULL;
	return (list);
}

void	lstadd_back(t_words **lst, t_words *new)
{
	t_words	*a;

	if (!new)
		return ;	
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	a = *lst;
	while (a->next)
		a = a->next;
	a->next = new;
}