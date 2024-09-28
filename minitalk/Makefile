# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xhan <xhan@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/19 14:21:12 by xhan              #+#    #+#              #
#    Updated: 2024/09/28 10:34:57 by xhan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER_SRCS	= server.c utils.c
CLIENT_SRCS	= client.c utils.c
HEADERS		= minitalk.h

CC			= cc -Wall -Werror -Wextra
CC_FLAGS	= -Lft_printf -lftprintf -Lft_printf/libft -lft

OBJ_SERVER	= ${SERVER_SRCS:.c=.o}
OBJ_CLIENT	= ${CLIENT_SRCS:.c=.o}

%.o: %.c ${HEADERS} ft_printf/libft.a ft_printf/libftprintf.a
			${CC} $< -c -o $@

all:		ft_printf server client

ft_printf:
			@make -C ft_printf

server:		${OBJ_SERVER} ${HEADERS}
			${CC} ${OBJ_SERVER} ${CC_FLAGS} -o server

client:		${OBJ_CLIENT} ${HEADERS}
			${CC} ${OBJ_CLIENT} ${CC_FLAGS} -o client

clean:
			rm -rdf ${OBJ_SERVER} ${OBJ_CLIENT}
			@make clean -C ft_printf

fclean:		clean
			rm -rdf client server
			@make fclean -C ft_printf

re:			fclean all

.PHONY:		all ft_printf clean fclean re
