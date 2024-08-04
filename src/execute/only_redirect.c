/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:13:04 by cadenegr          #+#    #+#             */
/*   Updated: 2024/08/02 16:06:51 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	continue_send_cmds(char *str, char **env, t_m *m)
{
	m->i++;
	if (!strncmp(str, "trunc\n", ft_strlen(str)))
	{
		copy_file("results", "outcome");
		save_in_file_trunc(NULL, m->cmds[m->i]);
	}
	else if (!strncmp(str, "append\n", ft_strlen(str)))
	{
		copy_file("results", "outcome");
		save_in_file_append(NULL, m->cmds[m->i]);
	}
	else if (!strncmp(str, "read\n", ft_strlen(str)))
		normal_pipex(m->cmds[0], "cat", env);
	else if (!strncmp(str, "delimit\n", ft_strlen(str)))
		normal_pipex(m->cmds[m->i], "cat", env);
	else
		return ;
}

void	send_to_cmds_cont(char *str, char **env, t_m *m)
{
	if (!strncmp(str, "read\n", ft_strlen(str)))
	{
		m->in.exit_status = 1;
		f_exec_and_read(m->cmds[m->i], &m->in.exit_status,
			m->cmds[m->i + 1], env);
	}
	else if (!strncmp(str, "delimit\n", ft_strlen(str)))
	{
		m->in.exit_status = 2;
		f_exec_and_read(m->cmds[m->i], &m->in.exit_status,
			m->cmds[m->i + 1], env);
	}
}

void	send_to_cmds(char *str, char **env, t_m *m)
{
	if (m->i)
		continue_send_cmds(str, env, m);
	else if (!strncmp(str, "trunc\n", ft_strlen(str)))
	{
		m->in.exit_status = 1;
		exec_and_file(m->cmds[m->i], &m->in.exit_status, "outcome", env);
		save_in_file_trunc(NULL, m->cmds[m->i + 1]);
	}
	else if (!strncmp(str, "append\n", ft_strlen(str)))
	{
		m->in.exit_status = 2;
		exec_and_file(m->cmds[m->i], &m->in.exit_status, "outcome", env);
		save_in_file_append(NULL, m->cmds[m->i + 1]);
	}
	else
		send_to_cmds_cont(str, env, m);
	if (!m->i)
		m->i++;
}

int	close_checkoutmaker(char *last_cmd, char **env, t_m *m)
{
	if (!ft_strcmp(last_cmd, "trunc\n"))
		copy_file("outcome", m->cmds[m->i]);
	else if (!ft_strcmp(last_cmd, "append\n"))
		copy_file_append("outcome", m->cmds[m->i]);
	else
	{
		m->in.exit_status = 1;
		exec_and_read("cat", &m->in.exit_status, "outcome", env);
	}
	unlink("outcome");
	free (last_cmd);
	ft_free_arr(m->cmds);
	return (1);
}

int	checkout_redirect(int read, char *input, char **env, t_m *m)
{
	int		fd;
	char	*str;
	char	*last_cmd;

	fd = open(m->files[3], O_RDONLY);
	add_t_history(m, input);
	if (fd == -1)
		return (0);
	while (read > 0)
	{
		str = get_next_line(fd);
		if (ft_strncmp(str, "command\n", ft_strlen(str)))
			send_to_cmds(str, env, m);
		if (read == 2)
			last_cmd = ft_strdup(str);
		free(str);
		read--;
	}
	close(fd);
	close_checkoutmaker(last_cmd, env, m);
	return (1);
}
