# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbjaghou <nbjaghou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/10 17:30:50 by nbjaghou          #+#    #+#              #
#    Updated: 2021/06/13 16:34:01 by nbjaghou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC =	ft_pipe.c \
		ft_split.c \
		join_path.c \
		pipex.c \
		search_path.c \
		utils.c \
		ft_strncmp.c \
		ft_stock_env.c \

OBJ = 	ft_pipe.o \
		ft_split.o \
		join_path.o \
		pipex.o \
		search_path.o \
		utils.o \
		ft_strncmp.o 	\
		ft_stock_env.o \

FLAGS = -Wall -Wextra -Werror 

all : $(NAME)

$(NAME) : ${OBJ}
	gcc -o $(NAME) ${OBJ} ${FLAGS}

.c.o : ${SRC}
		gcc -c $< -o ${<:.c=.o}

clean :
	/bin/rm -f $(OBJ)

fclean : clean
	/bin/rm -f $(NAME)

re : fclean all



