/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyagbasa <fyagbasa@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 16:49:12 by fyagbasa          #+#    #+#             */
/*   Updated: 2026/01/01 19:20:13 by fyagbasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_words	*lst_new(char *word, char type, int space_check)
{
	t_words	*list;

	list = (t_words *)malloc(sizeof(t_words));
	if (!list)
		return (0);
	list->word = word;
	list->space_check = space_check;
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

int	lst_count(t_words *words)
{
	int	a;

	a = 0;
	while (words)
	{
		if (!(words->type == 'w' && words->word[0] == '\0'))
			a++;
		words = words->next;
	}
	return (a);
}