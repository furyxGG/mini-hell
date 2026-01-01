/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyagbasa <fyagbasa@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 18:27:42 by fyagbasa          #+#    #+#             */
/*   Updated: 2026/01/01 14:54:06 by fyagbasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_variable_name(t_words *word)
{
	char	*tmp;
	char	*tmp2;
	int		a;

	tmp = ft_strchr(word->word, '$');
	a = 1;
	while (ft_isalnum(tmp[a]) && tmp[a])
		a++;
	tmp2 = ft_substr(tmp, 1, a - 1);
	return(tmp2);
}

static char	*first_part(t_words *words)
{
	char	*tmp;
	int		a;

	tmp = ft_strchr(words->word, '$');
	a = tmp - words->word;
	return (ft_substr(words->word, 0, a));
}

static char	*last_part(t_words *words)
{
	char	*tmp;
	char	*vari_n;
	int		a;

	vari_n = get_variable_name(words);
	tmp = ft_strnstr(words->word, vari_n, ft_strlen(words->word));
	a = ft_strlen(words->word) - (tmp - words->word) - ft_strlen(vari_n) + 1;
	return (ft_substr(tmp, ft_strlen(vari_n), a));
}

static void	do_changes(t_words *words)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	char	*tmp4;
	
	if (words->type == 'w' || words->type == 'Q')
	{
		tmp = first_part(words);
		tmp2 = get_variable_name(words);
		if (getenv(tmp2) == NULL)
			tmp4 = ft_strdup("");
		else
			tmp4 = ft_strdup(getenv(tmp2));
		free(tmp2);
		tmp3 = join_free(tmp, tmp4);
		tmp = last_part(words);
		tmp2 = join_free(tmp3, tmp);
		free(words->word);
		words->word = tmp2;
	}
}

void	expansion(t_words *words)
{
	t_words	*tmp;

	tmp = words;
	while (tmp)
	{
		if (tmp->type != '\'')
		{
			while (ft_strchr(tmp->word, '$'))
				do_changes(tmp);
		}
		tmp = tmp->next;
	}
}


//asdfsadf "naber $USER nasılsın?" selam $USER 'bir de böyle bakalım $USER'