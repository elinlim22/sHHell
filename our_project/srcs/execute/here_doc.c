/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:31:42 by huipark           #+#    #+#             */
/*   Updated: 2023/01/18 13:58:41 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#define UNLINK 0
#define HEREDOC 1

void	here_doc(t_cmd *cmd, char *file)
{
	char	*line;
	int		fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (line)
			line[ft_strlen(line) - 1] = '\0';
		if (!line || !ft_strcmp(line, cmd->red->str))
		{
			free(line);
			break ;
		}
		line[ft_strlen(line)] = '\n';
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close (fd);
	exit(0);
}

static void	parent_or_child(int pid, t_cmd *cmd, int cnt)
{
	char	*file;
	char	*temp;

	temp = ft_itoa(cnt);
	file = ft_strjoin(".temp_here_doc", temp);
	free (temp);
	if (pid == -1)
		perror("miniHell : fork_error");
	else if (pid == 0)
	{
		heredoc_signal();
		here_doc(cmd, file);
	}
	else
	{
		while (wait (0) != -1)
			;
		free(cmd->red->str);
		cmd->red->str = file;
		cmd->red->type = LEFT;
	}
}

void	search_red(int pid, t_cmd *cmd, int cnt)
{
	while (cmd->red->next)
	{
		cmd->red = cmd->red->next;
		if (cmd->red->type == DLFT)
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			pid = fork();
			parent_or_child(pid, cmd, cnt);
		}
	}
}

void	here_doc_check(t_cmd *cmd, int flag)
{
	static int	cnt;
	t_red		*red_head;
	int			pid;

	red_head = cmd->red;
	pid = 0;
	if (flag == HEREDOC)
	{
		search_red(pid, cmd, cnt);
		cnt++;
	}
	else if (flag == UNLINK)
	{
		pid = fork();
		if (pid == -1)
			perror("miniHell : fork_error");
		else if (pid == 0)
		{
			while (cnt >= 0)
				unlink(ft_strjoin(".temp_here_doc", ft_itoa(cnt--)));
			exit (0);
		}
	}
	cmd->red = red_head;
}
