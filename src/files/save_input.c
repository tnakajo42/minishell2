/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:13:43 by cadenegr          #+#    #+#             */
/*   Updated: 2024/07/30 12:13:45 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_file(char *src, char *dest)
{
	int		fd_src;
	char	*line;

	fd_src = open (src, O_RDONLY);
	if (fd_src == -1)
		return ;
	save_in_file_trunc(NULL, dest);
	while (1)
	{
		line = get_next_line(fd_src);
		if (!line)
			break ;
		ft_strtrim_noret(line, "\n");
		if (line[0] != '\0' || line[0] != '\n')
			save_in_file_append(line, dest);
		free (line);
	}
	if (line)
		free (line);
	close (fd_src);
	unlink(src);
}

void	copy_file_append(char *src, char *dest)
{
	int		fd_src;
	char	*line;

	fd_src = open (src, O_RDONLY);
	if (fd_src == -1)
		return ;
	while (1)
	{
		line = get_next_line(fd_src);
		if (!line)
			break ;
		ft_strtrim_noret(line, "\n");
		if (line[0] != '\0' || line[0] != '\n')
			save_in_file_append(line, dest);
		free (line);
	}
	if (line)
		free (line);
	close (fd_src);
	unlink(src);
}

void	remove_files(char **files)
{
	int	i;

	if (!files)
		return ;
	i = -1;
	while (files[++i])
		unlink(files[i]);
	if (files)
		ft_free_arr(files);
}

void	save_in_file_trunc(char *data, char *file_name)
{
	int		fd;

	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		perror("Failed to open file.-");
		return ;
	}
	if (data != NULL)
		ft_putendl_fd(data, fd);
	close (fd);
}

void	save_in_file_append(char *data, char *file_name)
{
	int		fd;

	fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
	{
		perror("Failed to open file.-");
		return ;
	}
	if (data != NULL)
		ft_putendl_fd(data, fd);
	close (fd);
}
