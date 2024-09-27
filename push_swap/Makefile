# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xhan <xhan@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/01 12:53:37 by xhan              #+#    #+#              #
#    Updated: 2024/09/23 19:05:28 by xhan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
ARCHIVE = push_swap.a
CC = cc
CFLAGS = -Wall -Werror -Wextra
MAKE_LIB = ar -rcs

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(ARCHIVE)
	$(CC) $< -o $@

$(ARCHIVE) : $(OBJS)
	$(MAKE_LIB) $(ARCHIVE) $^

%.o : %.c 
	$(CC) $(CFLAGS) -c $< -o $@ 
	
clean :
	rm -f $(OBJS) $(ARCHIVE)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re