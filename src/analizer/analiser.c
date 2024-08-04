/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analiser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:44:42 by tnakajo           #+#    #+#             */
/*   Updated: 2024/07/31 14:44:05 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_checkout(t_m *m)
{
	int		fd;
	char	*str;
	int		flag;

	fd = open(m->files[3], O_RDONLY);
	if (fd == -1)
		return (0);
	flag = 0;
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		flag++;
		free(str);
	}
	if (str)
		free (str);
	close(fd);
	return (flag * (flag % 2));
}

void	what_is(char *str, t_m *m)
{
	if (!ft_strncmp(str, ">\n", ft_strlen(str)))
		save_in_file_append("trunc", m->files[3]);
	else if (!ft_strncmp(str, ">>\n", ft_strlen(str)))
		save_in_file_append("append", m->files[3]);
	else if (!ft_strncmp(str, "<\n", ft_strlen(str)))
		save_in_file_append("read", m->files[3]);
	else if (!ft_strncmp(str, "<<\n", ft_strlen(str)))
		save_in_file_append("delimit", m->files[3]);
	else if (!ft_strncmp(str, "|\n", ft_strlen(str)))
		save_in_file_append("pipe", m->files[3]);
	else if (!ft_strncmp(str, "||\n", ft_strlen(str)))
		save_in_file_append("OR", m->files[3]);
	else
		save_in_file_append("command", m->files[3]);
}

int	checkout_visual(t_m *m)
{
	int		fd;
	char	*str;
	char	*temp;
	int		flag;

	fd = open(m->files[2], O_RDONLY);
	flag = 0;
	save_in_file_trunc(NULL, m->files[3]);
	while (1)
	{
		str = get_next_line(fd);
		temp = ft_strtrim(str, "\n");
		if (!temp)
			flag = 1;
		if (temp[0] == '\n' || temp[0] == '\0')
			flag = 1;
		if (!flag)
			what_is(temp, m);
		free(str);
		free (temp);
		if (flag == 1)
			break ;
	}
	close(fd);
	return (1);
}

int	analize(t_m *m)
{
	static int	placement = 1;
	int			i;
	int			fd;
	char		*line;

	fd = open (m->files[1], O_RDONLY);
	if (fd == -1)
		return (0);
	i = 0;
	while (i < placement)
	{
		line = get_next_line(fd);
		if (!line)
			return (0);
		if (i + 1 == placement)
			break ;
		free (line);
		i++;
	}
	init_struct_input(m);
	i = check_line(line, m);
	free (line);
	close (fd);
	placement++;
	return (i);
}
