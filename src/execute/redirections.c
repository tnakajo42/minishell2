/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:13:17 by cadenegr          #+#    #+#             */
/*   Updated: 2024/07/30 12:13:19 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_line(int fd)
{
	char	*line;

	line = NULL;
	line = get_next_line(fd);
	ft_strtrim_noret(line, " \n");
	return (line);
}

void	left_redirections(t_m *m, char *input, char **env)
{
	int		fd;
	int		type;
	char	*cmd;
	char	*file;

	fd = open(m->files[2], O_RDONLY);
	add_t_history(m, input);
	type = 0;
	while (1)
	{
		cmd = extract_line(fd);
		file = extract_line(fd);
		if (!ft_strcmp(file, "<"))
			type = 1;
		if (!ft_strcmp(file, "<<"))
			type = 2;
		free (file);
		file = extract_line(fd);
		break ;
	}
	m->in.exit_status = type;
	exec_and_read(cmd, &m->in.exit_status, file, env);
	free(cmd);
	free(file);
	close(fd);
}

int	find_type(char *file)
{
	int	type;

	type = 0;
	if (!ft_strcmp(file, ">"))
		type = 1;
	if (!ft_strcmp(file, ">>"))
		type = 2;
	return (type);
}

void	right_redirections(t_m *m, char *input, char **env)
{
	int		fd;
	int		type;
	char	*cmd;
	char	*file;

	fd = open(m->files[2], O_RDONLY);
	add_t_history(m, input);
	while (1)
	{
		cmd = extract_line(fd);
		file = extract_line(fd);
		type = find_type(file);
		free (file);
		file = extract_line(fd);
		break ;
	}
	m->in.exit_status = type;
	if (type == 0)
		left_redirections(m, input, env);
	else
		exec_and_file(cmd, &m->in.exit_status, file, env);
	free(cmd);
	free(file);
	close(fd);
}
