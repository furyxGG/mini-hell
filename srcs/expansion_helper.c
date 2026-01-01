/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyagbasa <fyagbasa@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 15:30:45 by fyagbasa          #+#    #+#             */
/*   Updated: 2026/01/01 16:26:23 by fyagbasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	*tmp2;
	char	*vari_n;
	int		a;

	vari_n = get_variable_name(words);
	tmp = ft_strnstr(words->word, vari_n, ft_strlen(words->word));
	a = ft_strlen(words->word) - (tmp - words->word) - ft_strlen(vari_n) + 1;
	tmp2 = ft_substr(tmp, ft_strlen(vari_n), a);
	free(vari_n);
	return (tmp2);
}

void	expansion_helper(t_words *words)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	char	*tmp4;
	
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

void	expansion_helper_null(t_words *words)
{
	char	*tmp;
	char	*tmp2;
	
	tmp = first_part(words);
	tmp2 = ft_strjoin(tmp, "$");
	free(words->word);
	free(tmp);
	words->word = tmp2;
}

void	expansion_helper_s_code(t_words *words)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	int		len;
	
	tmp = first_part(words);
	tmp2 = ft_itoa(g_status_code);
	tmp3 = join_free(tmp, tmp2);
	len = ft_strlen(ft_strchr(words->word, '?')) - 1;
	tmp = ft_substr(ft_strchr(words->word, '?'), 1, len);
	tmp2 = join_free(tmp3, tmp);
	free(words->word);
	words->word = tmp2;
}