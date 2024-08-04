/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:10:19 by cadenegr          #+#    #+#             */
/*   Updated: 2024/07/30 12:10:22 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	continue_extract_double_q(const char *line, t_m *m)
{
	int		i;
	char	*extract;

	i = -1;
	while (line[++i] && ft_isquotes(line[i]) != 2)
		if (line[i] == '\'')
			break ;
	if (line[i] == '\'')
	{
		extract = ft_strtrim_start(line, (i));
		ft_lstadd_back(&m->lst, ft_lstnew(extract));
		extract_single_q(line, m);
	}
	else
	{
		extract = ft_strtrim_start(line, i);
		extract = ft_strtrim(extract, "\"");
		m->in.quoted_words--;
		ft_lstadd_back(&m->lst, ft_lstnew(extract));
	}
	return (1);
}

int	input_whitespace(const char *line)
{
	int		i;
	char	*extract;
	char	*temp;

	i = 0;
	temp = NULL;
	temp = ft_strdup(line);
	while (line[i] && ft_iswhitespace(line[i]))
		i++;
	extract = ft_strtrim_start(line, i);
	free (extract);
	free (temp);
	return (i);
}

int	extract_printable(const char *line, t_m *m)
{
	int		i;
	char	*extract;

	if (ft_isalnum(line[0]))
		return (extract_alpha(line, m));
	i = -1;
	while (line[++i] && ft_isprint(line[i]) && !ft_isquotes(line[i]))
	{
		if (line[i] == '>')
			break ;
		else if (line[i] == '<')
			break ;
		if (line[i] == '|')
			break ;
	}
	if (line[i] != '>' && line[i] != '<' && line[i] != '|')
	{
		extract = ft_strtrim_start(line, i);
		ft_lstadd_back(&m->lst, ft_lstnew(extract));
	}
	else
		i = extension_printable(line, m, i);
	return (i);
}

int	extract_moneysign(const char *line, t_m *m)
{
	int		i;
	char	*extract;

	i = 0;
	while (line[i] && !ft_iswhitespace(line[i]) && !ft_isquotes(line[i]))
		i++;
	if (line[i] == '"')
	{
		i++;
		extract = ft_strtrim_start(line, i);
		ft_strtrim_noret(extract, "\"");
	}
	else
		extract = ft_strtrim_start(line, i);
	ft_lstadd_back(&m->lst, ft_lstnew(extract));
	return (i);
}

int	extract_whitespace(const char *line, t_m *m)
{
	int		i;
	char	*extract;

	i = 0;
	(void)m;
	while (line[i] && ft_iswhitespace(line[i]))
		i++;
	extract = ft_strtrim_start(line, i);
	free (extract);
	return (i);
}
