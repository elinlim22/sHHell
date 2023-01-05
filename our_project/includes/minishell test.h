/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell test.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 19:03:38 by hyeslim           #+#    #+#             */
/*   Updated: 2023/01/05 14:41:24 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <dirent.h> //opendir, readdir, closedir
# include <fcntl.h>
# include <readline/readline.h> //readline, rl_...
# include <signal.h>
# include <stdio.h>
# include <sys/ioctl.h> //ioctl
# include <sys/stat.h> //stat, lstat, fstat
# include <sys/wait.h>
# include <curses.h> //tgetent

enum e_pars
{
	STR, SPCE, SINQ, DOUQ, DOLR, \
	PIPE, \
	RIGT, DRGT, LEFT, DLFT
};

typedef struct	s_cmd
{
	char			*str;
	int				type;
	struct s_cmd	*next;
}				t_cmd;

typedef struct	s_redirection
{
	char					*str;
	int						type;
	struct s_redirection	*next;
}				t_red;

typedef struct s_token
{
	t_cmd			*cmd;
	t_red			*red;
	struct s_token	*next;
}				t_token;

#endif



// signal handling


/*
----------------------------------
예시 : cat < txt < txt < txt < txt2 | grep a >out > out > out2
txt		: hello my name is txt
txt2	: hello my name is txt2

ls
out out2 txt txt2

cat
out		: 아무것도 없음
out2	: hello my name is txt2

<	:	파이프 사이를 한 묶음 으로 보고 그 묶음에 < 여러개가 있으면 가장 마지막 file만
		STDIN으로 사용
>	:	일단 모든 file을 open 하고 가장 마지막의 file을 STDOUT으로 사용

|	*token node*
|	cmd : cat -> NULL
|	type: STR -> NULL
|	
|	red : txt -> txt -> txt -> txt2 -> NULL
|	type: LEFT-> LEFT-> LEFT-> LEFT -> NULL
|	
|	*token node next*
|	cmd : grep -> a -> NULL
|	type: STR  -> STR-> NULL
|	
|	red : out -> out -> out2
|	type: RIGT-> RIGT-> RIGT -> NULL
궁금한거 cmd는 무조건 STR
----------------------------------
----------------------------------
예시 : cat as0df |grep "as"

cat as0df : STR
| : PIPE
grep "as" : STR
----------------------------------

----------------------------------
예시 : < infile cat|grep "as" > outfile
< : LEFT
infile cat: STR
| : PIPE
grep "as" : STR
> : RIGT
outfile
----------------------------------


char *str 에 넣을것 : split을 할때 공백 기준으로 하되, |, <, >가 나오면 그냥 무조건 스플릿?
타입 : 아스키코드로 a~z = str a~z || 0~9 == str else

처음에 검사해야하는것?
1. 따옴표가 닫혀있는지 (짝수개인지_)
2. 세미콜론(;), 더블파이프(||), &, 백슬래시(\),				있으면 안됨
3.


cat as0df |grep "as" >
cat -e file | echo ji << outfile | cat | cat | cat | cat | cat |grep "as"
< infile ls -al | grep "as" > outfile

*/
