/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakajo <tnakajo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:48:19 by tnakajo           #+#    #+#             */
/*   Updated: 2024/07/30 10:57:14 by tnakajo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_continue_quotes_travel(const char *line, char *extract, int i, t_m *m)
{
	if (ft_isquotes(line[0]) == 1)
		i = extract_single_q_sub(line, m, extract, i);
	else if (ft_isquotes(line[0]) == 2)
		i = extract_double_q_sub(line, m, extract, i);
	else
		ft_lstadd_back(&m->lst, ft_lstnew(extract));
	return (i);
}

int	money_check_on_single_q_island(char *extract, int i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (j < i + 1)
	{
		if (extract[k] == '$' || extract[k] == '\\' || \
		ft_isredirection(extract[k]) != 0 || extract[k] == '|')
		{
			ft_insert_char_in_str(extract, '\\', k);
			k++;
		}
		j++;
		k++;
	}
	return (i);
}

int	check_on_double_q_island(char *extract, int i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (j < i + 1)
	{
		if (extract[k] == '\\' || \
		ft_isredirection(extract[k]) != 0 || extract[k] == '|')
		{
			ft_insert_char_in_str(extract, '\\', k);
			k++;
		}
		j++;
		k++;
	}
	return (i);
}

int	extract_single_q_sub(const char *line, t_m *m, char *pre_extract, int i)
{
	int		j;
	char	*extract;
	char	*extract_plus;
	char	*extract_temp;

	i = 1;
	j = 0;
	while (line[i] && ft_isquotes(line[i]) != 1)
		i++;
	i++;
	extract_temp = ft_strtrim_start(line, i);
	ft_strtrim_noret(extract_temp, "\'");
	i = money_check_on_single_q_island(extract_temp, i);
	while (line[j] && !ft_iswhitespace(line[j]) && !ft_isquotes(line[j]) 
		&& !ft_isredirection(line[j]) && line[j] != '|')
	{
		i++;
		j++;
	}
	extract_plus = ft_strtrim_start(line, j);
	extract_temp = ft_strjoin_gnl_free_second(pre_extract, extract_temp);
	free(pre_extract);
	extract = ft_strjoin_gnl_free_second(extract_temp, extract_plus);
	free(extract_temp);
	return (ft_continue_quotes_travel(line, extract, i, m));
}

int	extract_double_q_sub(const char *line, t_m *m, char *pre_extract, int i)
{
	int		j;
	char	*extract;
	char	*extract_plus;
	char	*extract_temp;

	i = 1;
	j = 0;
	while (line[i] && ft_isquotes(line[i]) != 2)
		i++;
	i++;
	extract_temp = ft_strtrim_start(line, i);
	ft_strtrim_noret(extract_temp, "\"");
	while (line[j] && !ft_iswhitespace(line[j]) && !ft_isquotes(line[j]) 
		&& !ft_isredirection(line[j]) && line[j] != '|')
	{
		i++;
		j++;
	}
	extract_plus = ft_strtrim_start(line, j);
	extract_temp = ft_strjoin_gnl_free_second(pre_extract, extract_temp);
	free(pre_extract);
	extract = ft_strjoin_gnl_free_second(extract_temp, extract_plus);
	free(extract_temp);
	return (ft_continue_quotes_travel(line, extract, i, m));
}
