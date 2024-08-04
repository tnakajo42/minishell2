/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_right_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:24:41 by cadenegr          #+#    #+#             */
/*   Updated: 2024/07/30 12:33:59 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	child_one_append(char *cmd, char *file, char **env, t_p *p)
{
	t_m	m;
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		cmd = NULL;
	dup2 (fd, STDOUT_FILENO);
	close (fd);
	if (builtin_execute(&m, cmd, 0) != 4242)
		cmd = NULL;
	execute(cmd, env, p);
}

void	child_one_trunc(char *cmd, char *file, char **env, t_p *p)
{
	t_m	m;
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		cmd = NULL;
	dup2 (fd, STDOUT_FILENO);
	close (fd);
	if (builtin_execute(&m, cmd, 0) != 4242)
		cmd = NULL;
	execute(cmd, env, p);
}

int	exec_and_file(char *cmd, int *type, char *file, char **env)
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
			child_one_trunc(cmd, file, env, &p);
		if (*type == 2)
			child_one_append(cmd, file, env, &p);
	}
	waitpid(p.process_id, &status, 0);
	if (WIFEXITED(status))
		*type = WEXITSTATUS(status);
	return (1);
}
