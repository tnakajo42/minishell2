/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:06:18 by cadenegr          #+#    #+#             */
/*   Updated: 2024/08/02 13:26:04 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	go_exit_status_var(char *str, t_m *m, int fd)
{
	char	*exit_status;

	if (ft_strncmp(str, "$?\0", ft_strlen("$?\0") != 0))
		return (0);
	exit_status = NULL;
	exit_status = ft_itoa(m->in.exit_status);
	if (exit_status)
	{
		ft_putstr_fd(exit_status, fd);
		ft_putchar_fd(' ', fd);
		free (exit_status);
	}
	return (1);
}

int	get_doll_visual(char *str, int i, t_m *m)
{
	int	n;
	int	single;

	if (str[i - 2] == '\'')
		single = 1;
	n = 0;
	while (str[i] != ' ' && str[i] != '\0' && str[i] != '\n' && str[i] != '\'')
	{
		n++;
		i++;
	}
	if (str[i] == '\'')
		single = 2;
	if (single == 2)
		m->dollar_str = 1;
	return (n);
}

int	find_export_data_2(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		if (str[i] == '\\')
			return (-1);
	i = -1;
	while (str[++i])
		if (str[i] == 36)
			return (i);
	return (-1);
}

int	vis_echo_cmd_print(char *str, t_m *m, int i, int fd)
{
	char	*dest;

	if (m->in.back_slash_flag == 0 && str[i] == '$' && str[i + 1] == '?')
	{
		i++;
		ft_putnbr_fd(m->in.exit_status, fd);
	}
	else if (m->in.back_slash_flag == 0 && str[i] == '$' \
		&& str[i + 1] != '\0' && str[i + 1] != ' ' && str[i + 1] != '\'')
	{
		i++;
		dest = (char *)malloc(sizeof(char) * (get_doll_visual(str, i, m) + 1));
		i += get_dollar_data(dest, str, i) - 1;
		m->history.last_exit_status = show_dollar_data(dest, m, fd);
		free (dest);
	}
	else
	{
		m->in.back_slash_flag = 0;
		ft_putchar_fd(str[i], fd);
	}
	return (i);
}

int	find_export_data(char *str, t_m *m, int fd)
{
	int		i;

	if (!m->in.dollar)
		return (0);
	i = find_export_data_2(str);
	if (i == -1)
		return (0);
	else
	{
		i = -1;
		while (str[++i])
			i = vis_echo_cmd_print(str, m, i, fd);
		ft_putchar_fd(' ', fd);
	}
	return (1);
}
