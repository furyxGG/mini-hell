/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyagbasa <fyagbasa@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 18:27:42 by fyagbasa          #+#    #+#             */
/*   Updated: 2026/01/01 16:21:15 by fyagbasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_variable_name(t_words *word)
{
	char	*tmp;
	char	*tmp2;
	int		a;

	tmp = ft_strchr(word->word, '$');
	a = 1;
	if (ft_isdigit(tmp[1]))
	{
		while (ft_isdigit(tmp[a]) && tmp[a])
			a++;
		tmp2 = ft_substr(tmp, 1, a - 1);
	}
	else
	{
		while (ft_isalnum(tmp[a]) && tmp[a])
			a++;
		tmp2 = ft_substr(tmp, 1, a - 1);
	}
	return(tmp2);
}

static void	do_changes(t_words *words, int *checker)
{
	if (ft_strchr(words->word, '$')[1] == '?')
		expansion_helper_s_code(words);
	else if (!ft_isalnum(ft_strchr(words->word, '$')[1]))
	{
		expansion_helper_null(words);
		*checker = 1;
	}
	else if (words->type == 'w' || words->type == 'Q')
		expansion_helper(words);
}

void	expansion(t_words *words)
{
	t_words	*tmp;
	int		checker;

	tmp = words;
	checker = 0;
	while (tmp)
	{
		if (tmp->type != 'q')
		{
			while (ft_strchr(tmp->word, '$'))
			{
				if (checker != 0)
				{
					do_changes(tmp, &checker);
					checker = 0;
					break ;
				}
				do_changes(tmp, &checker);
			}
		}
		tmp = tmp->next;
	}
}


//asdfsadf "naber $USER nasılsın?" selam $USER 'bir de böyle bakalım $USER'
//"naber $USER" '$USER' $USER_$PWD $?$? $ " $USER " $9USER