/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stock_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 16:32:13 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/06/13 16:32:21 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_stock_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	g_data.envp = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		g_data.envp[i] = ft_strdup(envp[i]);
		i++;
	}
	g_data.envp[i] = NULL;
}
