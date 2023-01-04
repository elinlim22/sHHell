# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyeslim <hyeslim@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/11 14:01:08 by hyeslim           #+#    #+#              #
#    Updated: 2022/12/04 17:02:25 by hyeslim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Werror -Wextra
SRCS = ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_itoa.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c
BSRCS =  ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_db_lstnew.c \
		ft_db_lstadd_back.c \
		ft_db_lstadd_front.c \
		ft_db_lstdelone.c \
		ft_db_lstclear.c \
		ft_sort_int_tab.c \
		get_next_line_bonus.c \
		ft_printf.c \
		ft_printf_utils.c \
		put_err.c
OBJS = ${SRCS:.c=.o}
BOBJS = ${BSRCS:.c=.o}

ifdef WITH_BONUS
	OBJ_RESULT = ${OBJS} ${BOBJS}
else
	OBJ_RESULT = ${OBJS}
endif

all : ${NAME}

bonus :
	@make WITH_BONUS=1 all

${NAME} : ${OBJ_RESULT}
	@ar rcs ${NAME} $^

%.o: %.c
	@${CC} ${CFLAGS} -c $< -o $@

clean :
	@rm -rf ${OBJS} ${BOBJS}

fclean : clean
	@rm -rf ${NAME}

re :
	@make fclean
	@make all

.PHONY : all clean fclean re bonus
