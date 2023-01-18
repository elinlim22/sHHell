# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: huipark <huipark@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/03 17:50:45 by hyeslim           #+#    #+#              #
#    Updated: 2023/01/18 14:00:04 by huipark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

# compiler
CC = cc
CFLAGS = -Wall -Werror -Wextra
LINK_FLAG = -lreadline -L$(shell brew --prefix readline)/lib -I$(shell brew --prefix readline)/include #-L/opt/homebrew/opt/readline/lib -I/opt/homebrew/opt/readline/include
COMP_FLAG = -I includes/minishell.h

# directories
DIR = srcs/
BLTIN = ${DIR}builtin/
EXECU = ${DIR}execute/
PARSE = ${DIR}parsing/
SIGNL = ${DIR}signal/
UTILS = ${DIR}utils/

BLTIN_SRCS = echo exit export export_utils pwd unset env cd init_env_list
EXECU_SRCS = here_doc redirect redirect_utils run_cmd
PARSE_SRCS = checker chunk init iterator tokenizer sub_parsing
SIGNL_SRCS = signal signal_utils signal_utils2
UTILS_SRCS = free get_function

# srcs
SRCS = ${addsuffix .c, $(addprefix ${BLTIN}, ${BLTIN_SRCS})} \
		${addsuffix .c, $(addprefix ${EXECU}, ${EXECU_SRCS})} \
		${addsuffix .c, $(addprefix ${PARSE}, ${PARSE_SRCS})} \
		${addsuffix .c, $(addprefix ${SIGNL}, ${SIGNL_SRCS})} \
		${addsuffix .c, $(addprefix ${UTILS}, ${UTILS_SRCS})} \
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

.PHONY : all re clean fclean run
