# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyeslim <hyeslim@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/03 17:50:45 by hyeslim           #+#    #+#              #
#    Updated: 2023/01/04 23:29:25 by hyeslim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
DIR = srcs/
SRCS = main.c
OBJS = ${SRCS:.c=.o}
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address ##
LINK_FLAG = -lreadline
COMP_FLAG = -I minishell.h

all : ${NAME}

${NAME}	 :
	@make bonus -C libft
	@make clean -C libft
	@mv libft/libft.a ./
	@${CC} ${CFLAGS} ${COMP_FLAG} -c $(DIR)${SRCS}
	@${CC} ${CFLAGS} ${LINK_FLAG} $(OBJS) libft.a  -o ${NAME}
	@make clean

re :
	@make fclean
	@make all
	@make clean

clean :
	@rm -rf ${OBJS}

fclean :
	@make clean
	@rm -rf libft.a
	@rm -rf minishell.a
	@rm -rf $(NAME)

.PHONY : all re clean fclean
