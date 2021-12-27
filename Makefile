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
	./libft/ft_strlen.c \
	./libft/ft_strncmp.c \
	./libft/ft_strjoin.c \
	./libft/ft_putstr_fd.c \
	./libft/ft_split.c

SRCS_B = bonus.c \
	get_path.c \
	./libft/ft_strlen.c \
	./libft/ft_strncmp.c \
	./libft/ft_strjoin.c \
	./libft/ft_putstr_fd.c \
	./libft/ft_split.c

OBJS = ${SRCS:.c=.o}
OBJS_B = ${SRCS_B:.c=.o}

all: ${OBJS}
	gcc ${OBJS} -o ${NAME}

bonus:	${OBJS_B}
	gcc ${OBJS_B} -o ${BONUS}

clean:
	rm -f ${OBJS} ${OBJS_B}

fclean:
	rm -f ${OBJS} ${OBJS_B} ${NAME} ${BONUS}

re:	fclean all
