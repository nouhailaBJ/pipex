/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 19:47:44 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/06/13 16:32:52 by nbjaghou         ###   ########.fr       */
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

char	*ft_getenv(char *str)
{
	int	i;

	i = 0;
	while (g_data.envp[i])
	{
		if (ft_strncmp(g_data.envp[i], str, ft_strlen(str)) == 0)
			return (g_data.envp[i] + 5);
		i++;
	}
	return (NULL);
}

int 	search_path(char *line)
{
	char		*path;
	char		**all_path;
	int			i;
	char		*tmp;
	int			fd;

	all_path = ft_split(ft_getenv("PATH"), ':');
	i = 0;
	path = ft_strdup("");
	while (all_path[i])
	{
		tmp = path;
		path = join_path(all_path[i], line);
		free(tmp);
		fd = open(path, O_RDONLY);
		if (fd > 1)
			return (search_path_helper(path, all_path, i));
		free(all_path[i]);
		i++;
	}
	return (search_path_free(path, all_path));
}
