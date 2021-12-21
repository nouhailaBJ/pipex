/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 12:46:50 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/06/19 16:00:14 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_file(char *file)
{
	ft_putstr_fd("pipex: ", 1);
	ft_putstr_fd(file, 1);
	ft_putstr_fd(": ", 1);
	ft_putstr_fd(strerror(errno), 1);
	ft_putstr_fd("\n", 1);
}

void 	ft_pipex(char **av, char **envp)
{
	int	error;

	error = 0;
	ft_stock_env(envp);
	g_data.s1 = ft_split(av[2], ' ');
	g_data.s2 = ft_split(av[3], ' ');
	g_data.inp = open(av[1], O_RDONLY);
	g_data.out = open(av[4], O_WRONLY | O_TRUNC | O_CREAT,
			S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
	if (g_data.inp < 0)
		error_file(av[1]);
	if (g_data.s1[0] && search_path(g_data.s1[0], 1) == 0 && g_data.inp > 0)
		ft_not_found(g_data.s1[0]);
	if (g_data.s2[0] && search_path(g_data.s2[0], 2) == 0)
	{
		ft_not_found(g_data.s2[0]);
		error = 127;
	}
	if (g_data.out < 0)
	{
		error_file(av[4]);
		error = 1;
	}
	if (error)
		exit(error);
}

void	ft_not_found(char *cmd)
{
	ft_putstr_fd("pipex: ", 1);
	ft_putstr_fd(cmd, 1);
	ft_putstr_fd(": command not found\n", 1);
	g_ret = 127;
}

int 	main(int ac, char **av, char **envp)
{
	g_ret = 0;
	if (ac != 5)
	{
		ft_putstr_fd("Syntax Error: ./pipex file1 cmd1 cmd2 file2\n", 1);
		return (EXIT_FAILURE);
	}
	ft_pipex(av, envp);
	ft_pipe();
	if (WIFEXITED(g_data.status))
		g_ret = WEXITSTATUS(g_data.status);
	return (g_ret);
}
