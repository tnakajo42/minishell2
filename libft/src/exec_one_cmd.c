/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:24:41 by cadenegr          #+#    #+#             */
/*   Updated: 2024/08/01 13:52:31 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	is_error(int error_type, char *s)
{
	if (error_type == 0)
		ft_putstr_fd("Not enough arguments.\n", 2);
	if (error_type == 1)
	{
		ft_putstr_fd("There is no PATH.\n", 2);
		return ;
	}
	if (error_type == 2)
		ft_putstr_fd("The file discriptors couldn't be forked.\n", 2);
	if (error_type == 3)
		ft_putstr_fd("Process id failed.\n", 2);
	if (error_type == 4)
		ft_putstr_fd("File cannot be open.\n", 2);
	if (error_type == 5)
		ft_putstr_fd("Problem with the output file.\n", 2);
	if (error_type == 6)
	{
		printf("command not found: %s\n", s);
		exit(127);
	}
	if (error_type == 7)
		ft_putstr_fd("Error duplicating file descriptor.\n", 2);
	(void)s;
	exit (1);
}

void	init_struct(t_p *p)
{
	p->error_type = -1;
	p->path_position = -1;
	p->cmd_arg = NULL;
	p->path = NULL;
	p->exec_cmd = NULL;
	p->path_parts = NULL;
	p->substr = NULL;
	p->i = -1;
	p->j = -1;
	p->n_cmds = 0;
	p->n_pipes = 0;
	p->fd = NULL;
	p->file = 0;
	p->pid = NULL;
}

int	correct_argument(char **env, t_p *p)
{
	int	i;

	init_struct(p);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (p->path_position = i);
		i++;
	}
	is_error (1, 0);
	return (0);
}

void	child_one_cmd(char *cmd, char **env, t_p *p)
{
	execute(cmd, env, p);
}

int	exec_one_cmd(char *cmd, char **env, int *exit_status)
{
	t_p		p;
	int		status;

	if (!correct_argument(env, &p))
		return (0);
	p.process_id = fork();
	if (p.process_id == -1)
		is_error(3, 0);
	if (!p.process_id)
		child_one_cmd(cmd, env, &p);
	waitpid(p.process_id, &status, 0);
	if (WIFEXITED(status))
		*exit_status = WEXITSTATUS(status);
	return (1);
}
