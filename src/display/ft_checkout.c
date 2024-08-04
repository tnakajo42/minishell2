/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkout.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:12:34 by cadenegr          #+#    #+#             */
/*   Updated: 2024/08/01 15:21:55 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_line_checkout(int fd)
{
	char	*line;
	char	*temp;

	line = NULL;
	line = get_next_line(fd);
	temp = line;
	temp = ft_strtrim(line, "\n");
	free (line);
	return (temp);
}

int	save_checkout_send_super(char *types, char **env, t_m *m)
{
	m->checkout = ft_split(types, ':');
	if (types)
		free (types);
	super_pipex(m->cmds, m->checkout, env, &m->in.exit_status);
	ft_free_arr(m->cmds);
	ft_free_arr(m->checkout);
	return (1);
}

int	checkout_maker(int read, char *input, char **env, t_m *m)
{
	int		fd;
	char	*str;
	char	*types;

	fd = open(m->files[3], O_RDONLY);
	add_t_history(m, input);
	if (fd == -1)
		return (0);
	types = NULL;
	while (read > 0)
	{
		str = extract_line_checkout(fd);
		if (ft_strncmp(str, "command", ft_strlen(str)))
		{
			types = ft_strjoin_gnl(types, str);
			types = ft_strjoin_gnl(types, ":");
		}
		free(str);
		read--;
	}
	save_checkout_send_super(types, env, m);
	return (1);
}

char	*checkout_cmds_shorter(int read, int fd, char *str, char *cmds)
{
	while (read > 0)
	{
		str = extract_line(fd);
		if (ft_ispipe(str[0]))
			cmds = ft_strjoin_gnl(cmds, ":");
		else
		{
			if (!ft_isredirection(str[0]))
			{
				cmds = ft_strjoin_gnl(cmds, str);
				cmds = ft_strjoin_gnl(cmds, " ");
			}
			else
				cmds = ft_strjoin_gnl(cmds, "R");
		}
		free(str);
		read--;
	}
	close(fd);
	return (cmds);
}

int	checkout_cmds(int read, t_m *m)
{
	int		fd;
	char	*str;
	char	*cmds;

	fd = open(m->files[2], O_RDONLY);
	if (fd == -1)
		return (0);
	str = NULL;
	cmds = NULL;
	cmds = checkout_cmds_shorter(read, fd, str, cmds);
	m->cmds = ft_split(cmds, ':');
	free (cmds);
	return (1);
}
