/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:39:15 by tnakajo           #+#    #+#             */
/*   Updated: 2024/07/31 16:41:14 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_execute(t_m *m, char *str, int fd)
{
	int	i;

	i = 0;
	(void)fd;
	if (!ft_strncmp(str, "cd ", ft_strlen("cd") + 1))
		i = cd_cmd(str, m);
	else if (!ft_strncmp(str, "echo ", ft_strlen("echo") + 1))
		i = echo_cmd(str, m, 4);
	else if (!ft_strncmp(str, "env ", ft_strlen("env") + 1))
		env_cmd(str, m);
	else if (!ft_strncmp(str, "exit ", ft_strlen("exit") + 1))
		i = exit_cmd(str, m);
	else if (!ft_strncmp(str, "export ", ft_strlen("export") + 1))
		export_cmd(str, m);
	else if (!ft_strncmp(str, "pwd ", ft_strlen("pwd") + 1))
		i = pwd_cmd(str, m);
	else if (!ft_strncmp(str, "unset ", ft_strlen("unset") + 1))
		unset_cmd(str, m);
	else if (!ft_strncmp(str, "history ", ft_strlen("history") + 1))
		show_t_history(m);
	else
		i = 4242;
	return (i);
}

void	try_execute(t_m *m, char *input, char **env)
{
	int		fd;
	char	*str;
	char	*temp;

	fd = open(m->files[2], O_RDONLY);
	add_t_history(m, input);
	while (1)
	{
		str = get_next_line(fd);
		temp = str;
		temp = ft_strtrim(temp, "\n");
		if (temp[0] == '\n' || temp[0] == '\0')
			m->break_flag = 1;
		else
			m->break_flag = builtin_execute(m, temp, fd);
		if (m->break_flag == 4242)
			exec_one_cmd(temp, env, &m->in.exit_status);
		free (temp);
		free(str);
		if (m->break_flag == 1 || m->break_flag == 4242 || m->break_flag == 42)
			break ;
	}
	close(fd);
}

void	remove_newline(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}
