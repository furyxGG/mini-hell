/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyagbasa <fyagbasa@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 22:13:30 by fyagbasa          #+#    #+#             */
/*   Updated: 2026/01/01 22:43:03 by fyagbasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_paths(char	**paths)
{
	int	a;

	a = 0;
	while (paths[a])
	{
		free(paths[a]);
		a++;
	}
	free(paths);
}

static char	**path_parser(char	**envt)
{
	char	**paths;
	int		a;

	a = 0;
	paths = NULL;
	while (envt[a])
	{
		if (ft_strncmp(envt[a], "PATH=", 5) == 0)
		{
			paths = ft_split(envt[a] + 5, ':');
			break ;
		}
		a++;
	}
	return (paths);
}

static char	*find_cmd_path(char *cmd, char **envt)
{
    char    **paths;
    char    *temp;
    char    *full_path;
    int     a;
	
	if (!cmd)
		return (NULL);
    if (ft_strchr(cmd, '/') && access(cmd, F_OK | X_OK) == 0)
        return (ft_strdup(cmd));
    paths = path_parser(envt);
    if (!paths) 
		return (NULL);
    a = -1;
    while (paths[++a])
    {
        temp = ft_strjoin(paths[a], "/");
        full_path = ft_strjoin(temp, cmd);
        free(temp);
        if (access(full_path, F_OK | X_OK) == 0)
            return (free_paths(paths), full_path);
        free(full_path);
    }
    return (free_paths(paths), NULL);
}

void	find_path(t_cmd *cmd, char	**envt)
{
	t_cmd	*temp_cmd;

	temp_cmd = cmd;
	while (temp_cmd)
	{
		temp_cmd->path = find_cmd_path(temp_cmd->args[0], envt);
		temp_cmd = temp_cmd->next;
	}
}