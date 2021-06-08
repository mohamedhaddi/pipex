# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/21 07:20:17 by mhaddi            #+#    #+#              #
#    Updated: 2021/06/08 19:54:34 by mhaddi           ###   ########.fr        #
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
			  utils/raise_error.c \
			  utils/free_and_init.c \
			  utils/free_double_pointer_and_init.c
CC			= gcc
RM			= rm -f
CFLAGS		= -Wall -Wextra -Werror
DFLAGS		= -g -fsanitize=address
NAME		= pipex

all:		$(NAME)

$(NAME):	
			$(CC) $(CFLAGS) $(DFLAGS) $(SRCS) -o $(NAME)

clean:		
			$(RM) -r *.dSYM

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
