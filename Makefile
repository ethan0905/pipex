#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esafar <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/16 15:28:53 by esafar            #+#    #+#              #
#    Updated: 2021/12/16 19:32:18 by esafar           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = pipex.c \
	get_path.c \
	./libft/ft_strlen.c \
	./libft/ft_strncmp.c \
	./libft/ft_strjoin.c \
	./libft/ft_putstr_fd.c \
	./libft/ft_split.c

OBJS = ${SRCS:.c=.o}

all: ${OBJS}
	gcc ${OBJS} -o ${NAME}

clean:
	rm -f ${OBJS}

fclean:
	rm -f ${OBJS} ${NAME}

re:	fclean all
