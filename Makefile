# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/21 07:20:17 by mhaddi            #+#    #+#              #
#    Updated: 2021/06/10 17:35:35 by mhaddi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= main.c \
			  check_error.c \
			  mem_check.c \
			  set_command.c \
			  open_files.c \
			  create_pipe.c \
			  make_children.c \
			  strings.c \
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
