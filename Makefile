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

BONUS = bonus

SRCS = pipex.c \
	get_path.c \
	exit.c \
	error.c

SRCS_B = bonus.c \
	get_path.c \
	exit.c \
	error.c \

LIBFT = ./libft/ft_strlen.c \
	./libft/ft_strncmp.c \
	./libft/ft_strjoin.c \
	./libft/ft_putstr_fd.c \
	./libft/ft_split.c

GNL = 	./get_next_line/get_next_line.c \
	./get_next_line/get_next_line_utils.c

OBJS = ${SRCS:.c=.o}
OBJS_B = ${SRCS_B:.c=.o}
OBJS_L = ${LIBFT:.c=.o}
OBJS_G = ${GNL:.c=.o}

all: ${OBJS} ${OBJS_L}
	clang ${OBJS} ${OBJS_L} -o ${NAME}

.c.o:

bonus:	${OBJS_B} ${OBJS_G} ${OBJS_L}
	clang ${OBJS_B} ${OBJS_L} ${OBJS_G} -o ${BONUS}

clean:
	rm -f ${OBJS} ${OBJS_B} ${OBJS_L} ${OBJS_G}

fclean:
	rm -f ${OBJS} ${OBJS_B} ${OBJS_L} ${OBJS_G} ${NAME} ${BONUS}

re:	fclean all
