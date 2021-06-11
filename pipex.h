/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 17:19:23 by nbjaghou          #+#    #+#             */
/*   Updated: 2021/06/10 17:59:04 by nbjaghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>
typedef struct s_pipex
{
	char	**s1;
	char	**s2;
	char	*file1;
	char	*file2;
	int		inp;
	int		out;
	int		fd[2];
	pid_t	pid;
}			t_pipex;
t_pipex	g_data;
void	ft_pipe(void);
char	**ft_split(char const *s, char c);
char	*join_path(char const *s1, char const *s2);
int		search_path(char *line);
int		ft_not_found(char *cmd);
int		check_errors(void);
void	stock_args(char **av);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s);
void	ft_putstr_fd(char *s, int fd);
#endif
