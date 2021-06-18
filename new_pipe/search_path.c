/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 19:47:44 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/06/15 19:02:19 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int 	search_path_helper(char *path, char **tbl, int i, int nb)
{
	char	*tmp;

	if (nb == 1)
	{
		tmp = g_data.s1[0];
		g_data.s1[0] = ft_strdup(path);
		free(tmp);
	}
	else
	{
		tmp = g_data.s2[0];
		g_data.s2[0] = ft_strdup(path);
		free(tmp);
	}
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

int 	search_path(char *line, int nb)
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
			return (search_path_helper(path, all_path, i, nb));
		free(all_path[i]);
		i++;
	}
	return (search_path_free(path, all_path));
}
