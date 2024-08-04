/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:10:02 by cadenegr          #+#    #+#             */
/*   Updated: 2024/08/01 13:21:14 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if(char c, t_m *m)
{
	if (ft_isquotes(c) == 1)
		m->in.single_q++;
	if (ft_isquotes(c) == 2)
		m->in.double_q++;
	if (ft_isredirection(c) == 1)
		m->in.right_d++;
	if (ft_isredirection(c) == 2)
		m->in.left_d++;
	if (ft_isspecialsign(c) == 1)
		m->in.slash++;
	if (ft_isspecialsign(c) == 2)
		m->in.semicolon++;
	if (ft_isspecialsign(c) == 3)
		m->in.dollar++;
	if (ft_isspecialsign(c) == 4)
		m->in.question++;
	if (ft_isspecialsign(c) == 5)
		m->in.andsign++;
	m->in.is_alnum += ft_isalnum(c);
	m->in.is_pipe += ft_ispipe(c);
	m->in.is_whitespc += ft_iswhitespace(c);
	return (1);
}

int	extract_path(char *line)
{
	int		index;
	char	*extract;

	if (!line)
		return (0);
	ft_strtrim_noret(line, "\n");
	index = get_index(line, ' ');
	if (index == -1)
		index = ft_strlen(line);
	extract = ft_strtrim_start_nomodify(line, index);
	if (extract[ft_strlen(extract) - 1] == '/')
	{
		printf("%s: command not found\n", extract);
		free (extract);
		return (0);
	}
	if (access(extract, F_OK | X_OK) != 0)
	{
		printf("%s: command not found-\n", extract);
		free (extract);
		return (0);
	}
	free (extract);
	return (1);
}

int	line_content(char *line, t_m *m)
{
	int		i;
	int		place;

	m->in.input_len = ft_strlen(line);
	if (line[0] == '/')
	{
		if (!extract_path(line))
		{
			m->in.exit_status = 127;
			return (0);
		}
		place = get_index_reverse(line, '/');
		ft_strtrim_start_noret(line, place);
	}
	i = -1;
	while (line[++i])
		check_if(line[i], m);
	if (m->in.single_q || m->in.double_q)
		i = quotes(line, m);
	return (i);
}

int	ft_signal(int read, t_m *m)
{
	int	i;
	t_p	p;
	int	result;

	if (!checkout_cmds_redirect(read, m))
		return (0);
	i = -1;
	result = 0;
	while (m->cmds[++i])
		simu_exec_wout_execute(m->cmds[i], m->env, m, &p);
	ft_free_arr(m->cmds);
	if (result == 0)
		return (1);
	return (0);
}

int	check_line(char *line, t_m *m)
{
	int		results;
	char	*temp;

	temp = ft_strdup(line);
	results = line_content(temp, m);
	if (!results)
	{
		free (temp);
		return (0);
	}
	if (ft_strncmp(temp, "echo", ft_strlen("echo")) == 0)
		m->is_echo = true;
	ft_strtrim_noret(temp, "\n");
	while (m->in.input_len >= 0)
	{
		if (ft_extractor(temp, m) == 0)
			break ;
		m->in.input_len--;
	}
	free (temp);
	results = file_analize(line, m);
	return (results);
}
