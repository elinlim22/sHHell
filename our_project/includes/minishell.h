/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeslim <hyeslim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 19:03:38 by hyeslim           #+#    #+#             */
/*   Updated: 2023/01/12 15:217:5530 by hyeslim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

extern int	g_exit_status;

# include "../libft/libft.h"
# include <dirent.h> //opendir, readdir, closedir
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h> //readline, rl_...
# include <readline/history.h>
# include <signal.h>
# include <term.h>
# include <sys/ioctl.h> //ioctl
# include <sys/stat.h> //stat, lstat, fstat
# include <sys/wait.h>
# include <curses.h> //tgetent
# include <string.h> //strerror
# include <errno.h>

# define KEY 0
# define VALUE 1

enum e_pars
{
	STR = 1,
	SPCE,
	SINQ,
	DOUQ,
	DOLR,
	PIPE,
	RIGT,
	DRGT,
	LEFT,
	DLFT
};

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
}				t_tok;

typedef struct s_redirection
{
	char					*str;
	int						type;
	struct s_redirection	*next;
}				t_red;

typedef struct s_command
{
	t_tok				*tok;
	t_red				*red;
	int					STDIN_FD;
	int					STDOUT_FD;
	int					in_fd;
	int					out_fd;
	int					fd[2];
	struct s_command	*next;
	struct s_command	*prev;
}				t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}				t_env;

/* ------------ builtin directory ------------ */
// cd.c
int		check_dir(t_env *env, char *headto);
void	change_dir(t_env *env, char *headto);
void	set_oldpwd(t_env *env, char *path);
int		cd(t_tok *tok, t_env *env);

// echo.c
int	say_it(t_tok *tok);

// env.c
int		print_env(t_tok *tok, t_env env);
char	*ft_getenv(t_env *env, char *pathname);
t_env	*find_env(t_env *env, char *keyname, int key_or_value);

// exit.c
int		exit_check(t_tok *tok, t_cmd *cmd);
void	exit_argm_error(char *msg, char *argm, int status, t_cmd *cmd);

// export.c
int	run_export(t_tok *tok, t_env env);
// export_utils.c
void	env_newnode(t_env env, t_env *temp);
void	value_swap(t_env *copy_env,t_env *temp_env);
int		add_env(t_env *env, char *str);
t_env	*env_copy(t_env env);

// pwd.c
int	run_pwd(void);
// unset.c
int	run_unset(t_tok *tok, t_env *env);
/* ------------ execute directory ------------ */

/* ------------ parsing directory ------------ */
// checker.c

int		check_arg(char *str);

// chunk.c
t_cmd	*chunk(t_tok **tok);

// init.c
void	add_red(t_cmd *cmd);
void	init_red(t_cmd	*cmd);
void	add_tok(t_tok **tok, char *str, int type);
void	init_tok(t_tok **tok);

// iterator.c
void	explore_token(t_cmd *cmd);
void	redirection_tok(t_cmd *cmd);

// tokenizer.c
t_tok	*tokenize(char *str);
void	check_dollar(t_env *env, t_tok *tok)

/* ------------ signal directory ------------ */
// signal.c
void	sig_status(void);
void	handle_signal_on_newline(void);
void	handle_signal_while_cmd(void);
void	signal_redisplay(void);

// signal_utils.c
void	child_signal_sigint(int signal);
void	signal_sigint(int signal);
void	child_signal_sigquit(int signal);
void	child_signal_sigterm(int signal);
void	signal_sigterm(int signal);

/* ------------ utils directory ------------ */

// init_env_list.c
char	*get_env_key(char *line);
char	*get_env_value(char *line);
void	init_env(t_env *env, char *envp[]);

// free.c
void	free_cmd(t_cmd *cmd);
void	free_export(t_env *copy_env);

// run_cmd.c
void	run_cmd(t_cmd *cmd, t_env env, char *envp[]);

// main.c
t_cmd	*ready_to_run(char *str);
void	argc_check(int argc, char *argv[]);

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
|
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
