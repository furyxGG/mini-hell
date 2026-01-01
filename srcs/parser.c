/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyagbasa <fyagbasa@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 16:28:24 by fyagbasa          #+#    #+#             */
/*   Updated: 2026/01/01 17:40:33 by fyagbasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	helper_opers(char *line, int a, t_words **words)
{
	int start;
	int	space;

    start = a;
	if (line[a] == '|')
	{
		a++;
		space = (line[a] == ' ' || (line[a] >= 9 && line[a] <= 13));
		lstadd_back(words, lst_new(ft_substr(line, start, a - start), 'p', space));
	}
	else
	{
		if ((line[a] == '>' && line[a + 1] == '>') || 
			(line[a] == '<' && line[a + 1] == '<'))
			a += 2;
		else
			a++;
		space = (line[a] == ' ' || (line[a] >= 9 && line[a] <= 13));
		lstadd_back(words, lst_new(ft_substr(line, start, a - start), 'o', space));
	}
	return (a);
}

static int	helper_quotes(char *line, int a, t_words **words)
{
	int		start;
	int		space;
	char	quote;

	quote = line[a++];
	start = a;
	while (line[a] != quote && line[a])
		a++;
	if (line[a])
		space = (line[a + 1] == ' ' || (line[a + 1] >= 9 && line[a + 1] <= 13));
	else
		space = 0;
	if (quote == '\'')
		lstadd_back(words, lst_new(ft_substr(line, start, a - start), 'q', space));
	else
		lstadd_back(words, lst_new(ft_substr(line, start, a - start), 'Q', space));
	a++;
	return (a);
}

static int	helper_words(char *line, int a, t_words **words)
{
	int start;
	int	space;

	start = a;
	while (!ft_strchr("|<>\'\" ", line[a]))
		a++;
	space = (line[a] == ' ' || (line[a] >= 9 && line[a] <= 13));
	lstadd_back(words, lst_new(ft_substr(line, start, a - start), 'w', space));
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