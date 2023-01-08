# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyeslim <hyeslim@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/29 00:42:27 by hyeslim           #+#    #+#              #
#    Updated: 2023/01/08 22:30:53 by hyeslim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
CFLAGS = -Wall -Werror -Wextra
SRCS = pipex.c utils.c utils2.c
BSRCS = pipex_bonus.c utils_bonus.c utils2_bonus.c
OBJS = ${SRCS:.c=.o}
BOBJS = ${BSRCS:.c=.o}

ifdef WITH_BONUS
	OBJ_RESULT = ${BOBJS}
else
	OBJ_RESULT = ${OBJS}
endif

all : ${NAME}

bonus :
	@make fclean
	@make WITH_BONUS=1 all

${NAME} : ${OBJ_RESULT}
	@make bonus -C libft
	@make clean -C libft
	@mv libft/libft.a ./
	@ar rcs pipex.a ${OBJ_RESULT}
	@${CC} ${CFLAGS} ${OBJ_RESULT} libft.a pipex.a -o ${NAME}
	@make clean

%.o: %.c
	@${CC} ${CFLAGS} -c $< -o $@

clean :
	@rm -rf *.o

fclean : clean
	@rm -rf libft.a pipex.a
	@rm -rf ${NAME}

bre :
	@make fclean
	@make bonus
	@make clean

re :
	@make fclean
	@make all
	@make clean

.PHONY : all clean fclean re bre
