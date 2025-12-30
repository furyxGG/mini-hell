/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyagbasa <fyagbasa@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 16:28:24 by fyagbasa          #+#    #+#             */
/*   Updated: 2025/12/30 18:04:06 by fyagbasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	helper_opers(char *line, int a, t_words **words)
{
	int start;

    start = a;
	if (line[a] == '|')
	{
		a++;
		lstadd_back(words, lst_new(ft_substr(line, start, a - start), 'p'));
	}
	else
	{
		if ((line[a] == '>' && line[a + 1] == '>') || 
			(line[a] == '<' && line[a + 1] == '<'))
			a += 2;
		else
			a++;
		lstadd_back(words, lst_new(ft_substr(line, start, a - start), 'o'));
	}
	return (a);
}

static int	helper_quotes(char *line, int a, t_words **words)
{
	int		start;
	char	quote;

	quote = line[a++];
	start = a;
	while (line[a] != quote && line[a])
		a++;
	if (quote == '\'')
		lstadd_back(words, lst_new(ft_substr(line, start, a - start), 'q'));
	else
		lstadd_back(words, lst_new(ft_substr(line, start, a - start), 'Q'));
	a++;
	return (a);
}

static int	helper_words(char *line, int a, t_words **words)
{
	int start;

	start = a;
	while (!ft_strchr("|<>\'\" ", line[a]))
		a++;
	lstadd_back(words, lst_new(ft_substr(line, start, a - start), 'w'));
	return (a);
}

t_words	*parser(char *line)
{
    int     a;
    t_words *words;

    a = 0;
    words = NULL;
    while (line[a])
    {
        while (line[a] && (line[a] == ' ' || (line[a] >= 9 && line[a] <= 13)))
            a++;
        if (!line[a])
            break;
        if (ft_strchr("|<>", line[a]))
            a = helper_opers(line, a, &words);
        else if (line[a] == '\'' || line[a] == '\"')
            a = helper_quotes(line, a, &words);
        else
            a = helper_words(line, a, &words);
    }
	return (words);
}