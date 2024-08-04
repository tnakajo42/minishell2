/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_cmd_left_redirect.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:27:55 by cadenegr          #+#    #+#             */
/*   Updated: 2024/08/02 15:42:37 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	f_parent_delimiter(int *fd, char *delimit, t_p *p)
{
	char	*input;
	char	*output;

	(void)p;
	input = NULL;
	output = NULL;
	close (fd[0]);
	while (1)
	{
		input = readline("heredoc>");
		if (input == NULL || !input || ft_strcmp(input, delimit) == 0)
			break ;
		input = ft_strjoin_gnl(input, "\n");
		output = ft_strjoin_gnl(output, input);
		if (input)
			free (input);
	}
	ft_putstr_fd(output, fd[1]);
	if (input)
		free (input);
	if (output)
		free (output);
	close (fd[1]);
	exit(EXIT_SUCCESS);
}

void	f_child_child_delimiter(char *cmd, int *fd, char **env, t_p *p)
{
	close (fd[1]);
	dup2 (fd[0], STDIN_FILENO);
	dup2(p->fd_out, STDOUT_FILENO);
	close (fd[0]);
	close (p->fd_out);
	execute(cmd, env, p);
}

void	f_child_delimiter(char *cmd, char *delimit, char **env, t_p *p)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		exit (EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit (EXIT_FAILURE);
	if (!pid)
		f_child_child_delimiter(cmd, fd, env, p);
	if (pid)
		f_parent_delimiter(fd, delimit, p);
	waitpid (pid, NULL, 0);
}

void	f_child_read(char *cmd, char *file, char **env, t_p *p)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return ;
	dup2 (fd, STDIN_FILENO);
	dup2 (p->fd_out, STDOUT_FILENO);
	close (fd);
	close (p->fd_out);
	execute(cmd, env, p);
}

int	f_exec_and_read(char *cmd, int *type, char *file_delimit, char **env)
{
	t_p		p;
	int		status;

	if (!correct_argument(env, &p))
		return (0);
	p.fd_out = open("outcome", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (p.fd_out == -1)
		return (0);
	p.process_id = fork();
	if (p.process_id == -1)
		is_error(3, 0);
	if (!p.process_id)
	{
		if (*type == 1)
			f_child_read(cmd, file_delimit, env, &p);
		if (*type == 2)
			f_child_delimiter(cmd, file_delimit, env, &p);
	}
	close (p.fd_out);
	waitpid(p.process_id, &status, 0);
	if (WIFEXITED(status))
		*type = WEXITSTATUS(status);
	return (1);
}
