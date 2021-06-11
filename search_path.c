/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 19:47:44 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/06/10 19:50:24 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
int 	search_path_helper(char *path, char **tbl, int i)
{
	while (tbl[i])
	{
		free(tbl[i]);
		i++;
	}
	free(path);
	free(tbl);
	tbl = NULL;
	return (1);
}

int 	search_path_free(char *path, char **all_path)
{
	free(path);
	free(all_path);
	all_path = NULL;
	return (0);
}

int 	search_path(char *line)
{
	char		*path;
	char		**all_path;
	struct stat	stats;
	int			i;
	char		*tmp;

	all_path = ft_split(getenv("PATH"), ':');
	i = 0;
	path = ft_strdup("");
	while (all_path[i])
	{
		tmp = path;
		path = join_path(all_path[i], line);
		free(tmp);
		if (stat(path, &stats) == 0)
		{
			if (stats.st_mode & X_OK)
				return (search_path_helper(path, all_path, i));
			else
				ft_putstr_fd("pipex: permisison denied\n", 1);
		}
		free(all_path[i]);
		i++;
	}
	return (search_path_free(path, all_path));
}
