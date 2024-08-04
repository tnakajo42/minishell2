/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   super_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 10:33:44 by cadenegr          #+#    #+#             */
/*   Updated: 2024/08/02 16:31:32 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	handle_redirections(char **cmds, char **type, t_p *p)
{
	char	*ptr;
	int		i;

	i = p->i;
	ptr = extract_file(cmds[p->i], "R");
	if (!ptr || !type)
		return ;
	ptr = (ft_strtrim(ptr, " "));
	if (strcmp(type[p->i], "pipe") == 0)
		i++;
	if (strcmp(type[i], "read") == 0)
		super_read(ptr);
	else if (strcmp(type[i], "trunc") == 0)
		super_trunc(ptr);
	else if (strcmp(type[i], "append") == 0)
		super_append(ptr);
	else if (strcmp(type[i], "delimit") == 0)
		super_delimiter(ptr, p->fd[1]);
	free (ptr);
}

/* close_wait(p); */
int	enter_child(char **cmds, char **type, t_p *p, char **env)
{
	int		i;
	char	*cmd;
	t_m		m;

	handle_redirections(cmds, type, p);
	super_pipes (p);
	if (get_index(cmds[p->i], 'R') != -1)
		cmd = ft_strtrim_start(cmds[p->i], get_index(cmds[p->i], 'R'));
	else
		cmd = ft_strdup(cmds[p->i]);
	i = -1;
	while (++i < 2 * (p->n_pipes))
		close (p->fd[i]);
	if (builtin_execute(&m, cmd, 0) != 4242)
		return (0);
	if (super_exec_wout_execute(cmd, env, p))
		if (super_execute(cmd, env, p))
			return (0);
	return (1);
}

int	super_pipex(char **cmds, char **type, char **env, int *exit_status)
{
	t_p		p;

	if (!correct_argument(env, &p))
		return (0);
	how_many_pipes(cmds, &p);
	while (++p.i < (p.n_pipes))
		if (pipe(p.fd + p.i * 2) == -1)
			exit (EXIT_FAILURE);
	p.i = -1;
	while (++p.i < p.n_cmds)
	{
		p.pid[p.i] = fork();
		if (p.pid[p.i] == -1)
			exit (EXIT_FAILURE);
		if (p.pid[p.i] == 0)
		{
			if (enter_child(cmds, type, &p, env))
				exit(EXIT_SUCCESS);
		}
	}
	p.pid[p.i] = -1;
	close_wait(&p, exit_status);
	free (p.fd);
	free (p.pid);
	return (EXIT_SUCCESS);
}
