/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:24:41 by cadenegr          #+#    #+#             */
/*   Updated: 2024/08/01 17:29:40 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	child(char *cmd, int *fd, char **env, t_p *p)
{
	t_m		m;

	dup2 (fd[1], STDOUT_FILENO);
	close (fd[0]);
	close(fd[1]);
	if (builtin_execute(&m, cmd, 0) != 4242)
		cmd = NULL;
	execute(cmd, env, p);
}

void	parent(char *cmd, int *fd, char **env, t_p *p)
{
	t_m		m;

	dup2 (fd[0], STDIN_FILENO);
	close (fd[1]);
	close(fd[0]);
	if (builtin_execute(&m, cmd, 0) != 4242)
		cmd = NULL;
	execute (cmd, env, p);
}

int	pipex(char *c1, char *c2, char **env, int *exit_status)
{
	int		fd[2];
	t_p		p;
	int		status;

	if (!correct_argument(env, &p))
		return (0);
	if (pipe(fd) == -1)
		is_error(6, "pipex");
	p.process_id = fork();
	if (p.process_id == -1)
		is_error(6, "pipex");
	if (!p.process_id)
		child(c1, fd, env, &p);
	p.second_id_process = fork();
	if (!p.second_id_process)
		parent (c2, fd, env, &p);
	close (fd[0]);
	close(fd[1]);
	waitpid(p.process_id, &status, 0);
	if (WIFEXITED(status))
		*exit_status = WEXITSTATUS(status);
	waitpid(p.second_id_process, &status, 0);
	if (WIFEXITED(status))
		*exit_status = WEXITSTATUS(status);
	return (EXIT_SUCCESS);
}

/*
	// waitpid(p.process_id, NULL, 0);
	// waitpid(p.second_id_process, NULL, 0);
*/