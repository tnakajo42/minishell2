/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_pipex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:28:53 by cadenegr          #+#    #+#             */
/*   Updated: 2024/07/30 12:35:02 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	normal_child(char *cmd, int *fd, char **env, t_p *p)
{
	int	file_d;

	file_d = open ("outcome", O_RDONLY);
	if (file_d == -1)
		is_error(6, "normal_pipex3");
	dup2 (file_d, STDIN_FILENO);
	dup2 (fd[1], STDOUT_FILENO);
	close (file_d);
	close (fd[0]);
	close(fd[1]);
	execute(cmd, env, p);
}

void	normal_parent(char *cmd2, int *fd, char **env, t_p *p)
{
	int		file_d;

	file_d = open ("results", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file_d == -1)
		is_error(6, "normal_pipex4");
	dup2 (fd[0], STDIN_FILENO);
	dup2 (file_d, STDOUT_FILENO);
	close (file_d);
	close(fd[0]);
	close (fd[1]);
	execute (cmd2, env, p);
}

int	normal_pipex(char *cmd1, char *cmd2, char **env)
{
	int		fd[2];
	t_p		p;

	if (!correct_argument(env, &p))
		return (0);
	if (pipe(fd) == -1)
		is_error(6, "normal_pipex1");
	p.process_id = fork();
	if (p.process_id == -1)
		is_error(6, "normal_pipex2");
	if (!p.process_id)
		normal_child(cmd1, fd, env, &p);
	p.second_id_process = fork();
	if (p.second_id_process == 0)
		normal_parent (cmd2, fd, env, &p);
	close(fd[0]);
	close(fd[1]);
	waitpid(p.process_id, NULL, 0);
	waitpid(p.second_id_process, NULL, 0);
	copy_file("results", "outcome");
	return (EXIT_SUCCESS);
}
