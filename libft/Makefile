# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xhan <xhan@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/03 11:07:15 by xhan              #+#    #+#              #
#    Updated: 2024/06/04 22:56:16 by xhan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			= ft_isalpha.c ft_isdigit.c ft_isascii.c ft_isalnum.c ft_isprint.c \
				  ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_strlcpy.c ft_strlcpy.c \
				  ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strncmp.c \
				  ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c \
				  ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
				  ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
				  ft_putendl_fd.c ft_putnbr_fd.c ft_memmove.c ft_strrchr.c
				  
OBJS			= $(SRCS:.c=.o)

CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -I.

NAME			= libft.a

all:			$(NAME)

$(NAME):		$(OBJS)
				ar rcs $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)
