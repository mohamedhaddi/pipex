# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/21 07:20:17 by mhaddi            #+#    #+#              #
#    Updated: 2021/06/08 06:43:10 by mhaddi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= main.c \
			  utils/ft_split.c \
			  utils/ft_split_utils.c \
			  utils/ft_strdup.c \
			  utils/ft_strlen.c \
			  utils/ft_strjoin.c \
			  utils/ft_strlcpy.c \
			  utils/ft_strncmp.c \
			  utils/ft_raise_error.c \
			  utils/ft_free_double_pointer.c
CC			= clang
RM			= rm -f
CFLAGS		= -Wall -Wextra -Werror
DFLAGS		= -g -fsanitize=address
NAME		= pipex

all:		$(NAME)

$(NAME):	
			$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean:		
			$(RM) $(NAME)

fclean:		clean

re:			fclean all

.PHONY:		all clean fclean re