/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_sub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:59:33 by cadenegr          #+#    #+#             */
/*   Updated: 2024/08/02 12:59:47 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	checkout_cmds_redirect(int read, t_m *m)
{
	int		fd;
	char	*str;
	char	*cmds;

	fd = open(m->files[2], O_RDONLY);
	if (fd == -1)
		return (0);
	cmds = NULL;
	while (read > 0)
	{
		str = get_next_line(fd);
		ft_strtrim_noret(str, " \n");
		if (read % 2)
		{
			cmds = ft_strjoin_gnl(cmds, str);
			cmds = ft_strjoin_gnl(cmds, ":");
		}
		free(str);
		read--;
	}
	close(fd);
	m->cmds = ft_split(cmds, ':');
	free (cmds);
	return (1);
}
