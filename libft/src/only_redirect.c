/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:09:20 by cadenegr          #+#    #+#             */
/*   Updated: 2024/07/30 12:35:13 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	o_child_one_append(char *file, char **env, t_p *p)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2 (fd, STDOUT_FILENO);
	close (fd);
	execute("cat", env, p);
}

void	o_child_one_trunc(char *file, char **env, t_p *p)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2 (fd, STDOUT_FILENO);
	close (fd);
	execute("cat", env, p);
}

int	o_exec_and_file(int type, char *file, char **env)
{
	t_p		p;

	if (!correct_argument(env, &p))
		return (0);
	p.process_id = fork();
	if (p.process_id == -1)
		is_error(3, 0);
	if (!p.process_id)
	{
		if (type == 1)
			o_child_one_trunc(file, env, &p);
		if (type == 2)
			o_child_one_append(file, env, &p);
	}
	waitpid(p.process_id, NULL, 0);
	return (1);
}
