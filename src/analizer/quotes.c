/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:11:03 by cadenegr          #+#    #+#             */
/*   Updated: 2024/07/30 12:11:05 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_nested(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 34)
		{
			i++;
			while (line[i] && line[i] != 34)
				i++;
			if (line[i] != 34)
				return (0);
		}
		else if (line[i] == 39)
		{
			i++;
			while (line[i] && line[i] != 39)
				i++;
			if (line[i] != 39)
				return (0);
		}
		i++;
	}
	return (1);
}

int	quote_checker(char *line, t_m *m)
{
	if (m->in.double_q)
		return (if_nested(line));
	if (m->in.single_q)
		return (if_nested(line));
	return (0);
}

int	quotes(char *line, t_m *m)
{
	if (!quote_checker(line, m))
	{
		perror("quotes are wrong");
		return (0);
	}
	return (1);
}
