# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyeslim <hyeslim@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/03 17:50:45 by hyeslim           #+#    #+#              #
#    Updated: 2023/01/08 22:32:53 by hyeslim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minihell

# compiler
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address ##
LINK_FLAG = -lreadline
COMP_FLAG = -I includes/minishell.h

# directories
DIR = srcs/
BLTIN = ${DIR}builtin/
EXECU = ${DIR}execute/
PARSE = ${DIR}parsing/
SIGNL = ${DIR}signal/
UTILS = ${DIR}utils/

BLTIN_SRCS = cd echo exit export pwd unset env
EXECU_SRCS =
PARSE_SRCS = checker chunk init iterator tokenizer
SIGNL_SRCS = signal
UTILS_SRCS =

# srcs
SRCS = ${addsuffix .c, $(addprefix ${BLTIN}, ${BLTIN_SRCS})} \
		${addsuffix .c, $(addprefix ${EXECU}, ${EXECU_SRCS})} \
		${addsuffix .c, $(addprefix ${PARSE}, ${PARSE_SRCS})} \
		${addsuffix .c, $(addprefix ${SIGNL}, ${SIGNL_SRCS})} \
		${addsuffix .c, $(addprefix ${UTILS}, ${UTILS_SRCS})} \
		${DIR}free.c \
		${DIR}init_env_list.c \
		${DIR}main.c

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
