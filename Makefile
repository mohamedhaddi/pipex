# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/21 07:20:17 by mhaddi            #+#    #+#              #
#    Updated: 2021/06/18 16:30:25 by mhaddi           ###   ########.fr        #
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
BNS_SRCS	= src_bonus/main_bonus.c \
			  src_bonus/mem_check_bonus.c \
			  src_bonus/check_error_bonus.c \
			  src_bonus/set_command_bonus.c \
			  src_bonus/open_files_bonus.c \
			  src_bonus/create_pipe_bonus.c \
			  src_bonus/make_children_bonus.c \
			  src_bonus/strings_bonus.c \
			  src_bonus/get_next_line.c
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

bonus:
			$(CC) $(CFLAGS) $(DFLAGS) $(BNS_SRCS) -o $(NAME)

.PHONY:		all clean fclean re bonus
