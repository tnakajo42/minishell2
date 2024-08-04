/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakajo <tnakajo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:45:27 by tnakajo           #+#    #+#             */
/*   Updated: 2024/07/30 11:01:02 by tnakajo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	extract_redirections_in_q(const char *line, t_m *m)
{
	int		i;
	char	*extract;

	i = 0;
	while (line[i] && ft_isprint(line[i]) && !ft_isquotes(line[i]))
	{
		if (ft_ispipe(line[i]) || ft_isredirection(line[i]))
			break ;
		i++;
	}
	extract = ft_strtrim_start(line, i);
	return (ft_continue_quotes_travel(line, extract, i, m));
}

int	extract_single_q(const char *line, t_m *m)
{
	int		i;
	int		j;
	char	*temp;
	char	*extract;

	i = 1;
	j = 0;
	while (line[i] && ft_isquotes(line[i]) != 1)
		i++;
	i++;
	temp = ft_strtrim_start(line, i);
	ft_strtrim_noret(temp, "\'");
	i = money_check_on_single_q_island(temp, i);
	while (line[j] && !ft_iswhitespace(line[j]) && !ft_isquotes(line[j]) 
		&& !ft_isredirection(line[j]) && line[j] != '|')
	{
		i++;
		j++;
	}
	extract = ft_strjoin_gnl_free_second(temp, ft_strtrim_start(line, j));
	free (temp);
	return (ft_continue_quotes_travel(line, extract, i, m));
}

int	extract_double_q(const char *line, t_m *m)
{
	int		i;
	int		j;
	char	*temp;
	char	*extract;

	i = 1;
	j = 0;
	while (line[i] && ft_isquotes(line[i]) != 2)
		i++;
	i++;
	extract = ft_strtrim_start(line, i);
	ft_strtrim_noret(extract, "\"");
	i = check_on_double_q_island(extract, i);
	while (line[j] && !ft_iswhitespace(line[j]) && !ft_isquotes(line[j]) 
		&& !ft_isredirection(line[j]) && line[j] != '|')
	{
		i++;
		j++;
	}
	temp = ft_strtrim_start(line, j);
	extract = ft_strjoin_gnl(extract, temp);
	free (temp);
	return (ft_continue_quotes_travel(line, extract, i, m));
}

int	extract_right(const char *line, t_m *m)
{
	char	*extract;

	if (ft_isredirection(line[0]) == 1)
	{
		if (line[1] == '>')
		{
			if (line[2] == '>')
				return (error("minishell: parse error near `>'"));
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

int	extract_left(const char *line, t_m *m)
{
	char	*extract;

	if (ft_isredirection(line[0]) == 2)
	{
		if (line[1] == '<')
		{
			if (line[2] == '<')
				return (error("minishell: parse error near `<'"));
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
