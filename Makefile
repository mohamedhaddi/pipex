# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/21 07:20:17 by mhaddi            #+#    #+#              #
#    Updated: 2021/06/11 16:32:32 by mhaddi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= src/main.c \
			  src/mem_check.c \
			  src/check_error.c \
			  src/set_command.c \
			  src/open_files.c \
			  src/create_pipe.c \
			  src/make_children.c \
			  src/strings.c
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
