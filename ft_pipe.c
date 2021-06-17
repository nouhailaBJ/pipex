/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 17:23:56 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/06/15 18:47:42 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_pipe(void)
{
	pipe(g_data.fd);
	g_data.pid = fork();
	if (g_data.pid == -1)
		exit(EXIT_FAILURE);
	if (g_data.pid == 0)
	{
		dup2(g_data.fd[1], 1);
		dup2(g_data.inp, 0);
		close(g_data.fd[0]);
		close(g_data.fd[1]);
		execve(g_data.s1[0], g_data.s1, g_data.envp);
		exit(EXIT_FAILURE);
	}
	else
	{
		dup2(g_data.fd[0], 0);
		dup2(g_data.out, 1);
		close(g_data.fd[0]);
		close(g_data.fd[1]);
		execve(g_data.s2[0], g_data.s2, g_data.envp);
		exit(EXIT_FAILURE);
	}
	close(g_data.inp);
	close(g_data.out);
}
