/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:10:27 by cadenegr          #+#    #+#             */
/*   Updated: 2024/07/30 12:10:30 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	extension_printable(const char *line, t_m *m, int i)
{
	if (line[i] == '>')
		i = extract_right(line, m);
	if (line[i] == '<')
		i = extract_left(line, m);
	if (line[i] == '|')
		i = extract_pipe(line, m);
	return (i);
}

int	extension_double_q(const char *line, t_m *m)
{
	int	i;

	i = 0;
	if (line[0] == '\'')
		i = extract_single_q(line, m);
	if (line[0] == '$')
		i = continue_extract_double_q(line, m);
	return (i);
}

int	finish_double(const char *line, t_m *m)
{
	int		i;
	char	*extract;

	if (line[0] == '"')
	{
		extract = ft_strtrim_start(line, 1);
		ft_strtrim_noret(extract, "\"");
	}
	else
	{
		i = 0;
		while (line[i] && ft_isquotes(line[i]) != 2)
			i++;
		extract = ft_strtrim_start(line, i);
		ft_strtrim_noret(extract, "\"");
		ft_lstadd_back(&m->lst, ft_lstnew(extract));
	}
	m->in.out_double = true;
	return (i);
}

int	extract_pipe(const char *line, t_m *m)
{
	char	*extract;

	if (line[0] == '|')
	{
		if (line[1] == '|')
		{
			if (line[2] == '|')
				return (error("minishell: parse error near `|'"));
			else
				extract = ft_strtrim_start(line, 2);
		}
		else
			extract = ft_strtrim_start(line, 1);
	}
	ft_lstadd_back(&m->lst,
		ft_lstnew(extract));
	return (1);
}
