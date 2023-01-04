/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeslim <hyeslim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 19:03:38 by hyeslim           #+#    #+#             */
/*   Updated: 2023/01/04 23:28:57 by hyeslim          ###   ########.fr       */
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

typedef struct	s_shell
{
	char			*str;
	int				type;
	struct s_shell	*next;
}				t_shell;
// signal handling

#endif



/*
예시 : cat as0df |grep "as"

cat as0df : STR
| : PIPE
grep "as" : STR

예시 : < infile cat|grep "as" > outfile
< : LEFT
infile cat: STR
| : PIPE
grep "as" : STR
> : RIGT
outfile


char *str 에 넣을것 : split을 할때 공백 기준으로 하되, |, <, >가 나오면 그냥 무조건 스플릿?
타입 : 아스키코드로 a~z = str a~z || 0~9 == str else

처음에 검사해야하는것?
1. 따옴표가 닫혀있는지 (짝수개인지_)
2. 세미콜론(;), 더블파이프(||), &, 백슬래시(\),				있으면 안됨
3.


cat as0df |grep "as" >
cat -e file | echo ji << outfile | cat | cat | cat | cat | cat |grep "as"
< infile ls -al | grep "as" > outfile

cat
as0df
|
grep
"as"

노드1
str : cat
type : 0(STR)
next : 노드2

노드2
str : as0df
type : 0(STR)
next : 노드3

....


그다음에
노드를 읽으면서 | < >가 아니면 합쳐 2차원배열로

(구조체가 다른)노드1
str : {cat; as0df}
next

노드2
str : |
next

노드3
str : {grep; "as"}
next


*/
