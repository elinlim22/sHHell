# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyeslim <hyeslim@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/03 17:50:45 by hyeslim           #+#    #+#              #
#    Updated: 2023/01/07 21:28:51 by hyeslim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minihell
DIR = srcs/

SRCS =	${DIR}main.c \
		${DIR}tokenizer.c \
		${DIR}iterator.c \
		${DIR}init.c \
		${DIR}init_env_list.c \
		${DIR}chunk.c \
		$(DIR)checker.c \
		$(DIR)free.c
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address ##
LINK_FLAG = -lreadline
COMP_FLAG = -I includes/minishell.h

all : ${NAME}

${NAME}	 :
	@make bonus -C libft
	@make clean -C libft
	@mv libft/libft.a ./
	@${CC} ${CFLAGS} ${COMP_FLAG} ${LINK_FLAG} ${SRCS} libft.a -o ${NAME}
	@make clean

re :
	@make fclean
	@make all
	@make clean

clean :
	@rm -rf ${OBJS}
	@rm -rf libft.a

fclean :
	@make clean
	@rm -rf libft.a
	@rm -rf minishell.a
	@rm -rf $(NAME)

run :
	@make re
	@./${NAME}

.PHONY : all re clean fclean
