/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_left_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:58:49 by cadenegr          #+#    #+#             */
/*   Updated: 2024/07/30 14:33:02 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	parent_delimiter(int *fd, char *delimit)
{
	char	*input;
	char	*output;

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

void	child_child_delimiter(char *cmd, int *fd, char **env, t_p *p)
{
	t_m	m;

	close (fd[1]);
	dup2 (fd[0], STDIN_FILENO);
	close (fd[0]);
	if (builtin_execute(&m, cmd, 0) != 4242)
		cmd = NULL;
	execute(cmd, env, p);
}

void	child_delimiter(char *cmd, char *delimit, char **env, t_p *p)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		exit (EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit (EXIT_FAILURE);
	if (!pid)
		parent_delimiter(fd, delimit);
	if (pid)
	{
		waitpid (pid, NULL, 0);
		child_child_delimiter(cmd, fd, env, p);
	}
}

void	child_read(char *cmd, char *file, char **env, t_p *p)
{
	int	fd;
	t_m	m;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("minishell: %s: No such file or directory\n", file);
		exit (EXIT_FAILURE);
	}
	dup2 (fd, STDIN_FILENO);
	close (fd);
	if (builtin_execute(&m, cmd, 0) != 4242)
		cmd = NULL;
	execute(cmd, env, p);
}

int	exec_and_read(char *cmd, int *type, char *file_delimit,
	char **env)
{
	t_p		p;
	int		status;

	if (!correct_argument(env, &p))
		return (0);
	p.process_id = fork();
	if (p.process_id == -1)
		is_error(3, 0);
	if (!p.process_id)
	{
		if (*type == 1)
			child_read(cmd, file_delimit, env, &p);
		if (*type == 2)
			child_delimiter(cmd, file_delimit, env, &p);
	}
	waitpid(p.process_id, &status, 0);
	if (WIFEXITED(status))
		*type = WEXITSTATUS(status);
	return (1);
}
