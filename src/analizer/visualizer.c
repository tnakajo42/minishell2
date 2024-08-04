/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:11:10 by cadenegr          #+#    #+#             */
/*   Updated: 2024/07/31 16:23:22 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	write_str_num(char *s, int n, int fd)
{
	ft_putstr_fd(s, fd);
	if (n == -4242)
		return (1);
	ft_putnbr_fd(n, fd);
	return (1);
}

int	pipe_or_redirect(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (ft_ispipe(s[i]))
			return (1);
		if (ft_isredirection(s[i]))
			return (1);
	}
	return (0);
}

int	cont_file_analize(char *line, t_m *m, int fd)
{
	write_str_num("\n\n", -4242, fd);
	ft_putstr_fd(line, fd);
	write_str_num(" (\')<->", m->in.single_q, fd);
	write_str_num(" (\")<->", m->in.double_q, fd);
	write_str_num(" (>)<->", m->in.right_d, fd);
	write_str_num(" (<)<->", m->in.left_d, fd);
	write_str_num(" (|)<->", m->in.is_pipe, fd);
	write_str_num(" (\\)<->", m->in.slash, fd);
	write_str_num(" ($)<->", m->in.dollar, fd);
	write_str_num(" (?)<->", m->in.question, fd);
	write_str_num(" (&)<->", m->in.andsign, fd);
	write_str_num(" (whitspace)<->", m->in.is_whitespc, fd);
	return (1);
}

void	file_analize_loop(int fd, t_m *m)
{
	t_list	*temp;
	char	*content;

	ft_lstremove_if(&m->lst, is_empty);
	temp = m->lst;
	while (temp)
	{
		content = (char *)temp->content;
		if (find_export_data(content, m, fd))
			m->history.last_exit_status = 0;
		else if (ft_ispipe(content[0]) || ft_isredirection(content[0]))
		{
			ft_putstr_fd("\n", fd);
			ft_putendl_fd(content, fd);
		}
		else
		{
			ft_putstr_fd(content, fd);
			ft_putchar_fd(' ', fd);
		}
		temp = temp->next;
	}
	ft_lstclear(&temp, del);
	ft_lstclear(&m->lst, del);
}

int	file_analize(char *line, t_m *m)
{
	int		fd;

	fd = open(m->files[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (0);
	file_analize_loop(fd, m);
	cont_file_analize(line, m, fd);
	close (fd);
	m->history.last_exit_status = 0;
	checkout_visual(m);
	return (1);
}
