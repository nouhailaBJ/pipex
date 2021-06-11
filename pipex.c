/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 17:23:19 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/06/10 19:51:05 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free(char *tmp)
{
	free(tmp);
	tmp = NULL;
}

int 	ft_not_found(char *cmd)
{
	ft_putstr_fd("pipex: ", 1);
	ft_putstr_fd(cmd, 1);
	ft_putstr_fd(": command not found\n", 1);
	return (0);
}

int 	check_errors(void)
{
	int	error;

	error = 0;
	if (g_data.inp < 0)
	{
		ft_putstr_fd("pipex: ", 1);
		perror(g_data.file1);
		error = 1;
	}
	if (g_data.out < 0)
	{
		ft_putstr_fd("pipex: ", 1);
		perror(g_data.file2);
		error = 1;
	}
	if (g_data.s1[0] && search_path(g_data.s1[0]) == 0 && !error)
		ft_not_found(g_data.s1[0]);
	if (g_data.s2[0] && search_path(g_data.s2[0]) == 0)
		ft_not_found(g_data.s2[0]);
	if (error)
		exit(EXIT_FAILURE);
	return (1);
}

void	stock_args(char **av)
{
	g_data.file1 = av[1];
	g_data.file2 = av[4];
	g_data.s1 = ft_split(av[2], ' ');
	g_data.s2 = ft_split(av[3], ' ');
	g_data.inp = open(av[1], O_RDONLY);
	g_data.out = open(av[4], O_WRONLY | O_TRUNC | O_CREAT,
			S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
}

int 	main(int ac, char **av)
{
	if (ac == 5)
	{
		stock_args(av);
		if (check_errors())
		{
			if (g_data.file1 && g_data.file2 && g_data.s1[0] && g_data.s2[0])
				ft_pipe();
			else
				ft_putstr_fd("pipex: : command not found\n", 1);
		}
	}
	else
		ft_putstr_fd("Syntax Error: ./pipex file1 cmd1 cmd2 file2\n", 1);
}
