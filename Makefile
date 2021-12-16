# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esafar <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/16 15:28:53 by esafar            #+#    #+#              #
#    Updated: 2021/12/16 18:20:15 by esafar           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = pipex.c \
	./libft/ft_strlen.c \
	./libft/ft_strncmp.c \
	./libft/ft_strjoin.c \
	./libft/ft_putstr_fd.c

OBJS = ${SRCS:.c=.o}

all: ${OBJS}
	gcc ${OBJS} -o ${NAME}

clean:
	rm -f ${OBJS}

fclean:
	rm -f ${OBJS} ${NAME}

re:
	fclean
	all
