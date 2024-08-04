/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:42:28 by cadenegr          #+#    #+#             */
/*   Updated: 2024/07/30 12:34:52 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	f_child(char *cmd, int *fd, char **env, t_p *p)
{
	dup2 (fd[1], STDOUT_FILENO);
	close (fd[0]);
	close(fd[1]);
	execute(cmd, env, p);
}

void	f_parent(char *cmd, int *fd, char **env, t_p *p)
{
	int	fd_file;

	fd_file = open("outcome", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_file == -1)
		is_error(6, "f_pipex1");
	dup2 (fd[0], STDIN_FILENO);
	dup2 (fd_file, STDOUT_FILENO);
	close (fd[1]);
	close(fd[0]);
	close (fd_file);
	execute (cmd, env, p);
}

int	f_pipex(char *c1, char *c2, char **env)
{
	int		fd[2];
	t_p		p;

	if (!correct_argument(env, &p))
		return (0);
	if (pipe(fd) == -1)
		is_error(6, "f_pipex");
	p.process_id = fork();
	if (p.process_id == -1)
		is_error(6, "f_pipex");
	if (!p.process_id)
		f_child(c1, fd, env, &p);
	p.second_id_process = fork();
	if (!p.second_id_process)
		f_parent (c2, fd, env, &p);
	close (fd[0]);
	close(fd[1]);
	waitpid(p.process_id, NULL, 0);
	waitpid(p.second_id_process, NULL, 0);
	return (EXIT_SUCCESS);
}
