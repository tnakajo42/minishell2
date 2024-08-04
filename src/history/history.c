/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakajo <tnakajo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:14:06 by tnakajo           #+#    #+#             */
/*   Updated: 2024/07/30 11:14:07 by tnakajo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_t_history(t_m *m, const char *command)
{
	int	i;

	i = 1;
	if (command[0] == '\0')
		return ;
	if (m->history.count < MAX_HISTORY)
	{
		m->history.commands[m->history.count] = ft_strdup(command);
		m->history.count++;
	}
	else
	{
		free(m->history.commands[0]);
		while (i < MAX_HISTORY)
		{
			m->history.commands[i - 1] = m->history.commands[i];
			i++;
		}
		m->history.commands[MAX_HISTORY - 1] = ft_strdup(command);
	}
}

int	show_t_history(t_m *m)
{
	int	i;

	i = 0;
	while (m->history.count > i)
	{
		printf("    %i  %s\n", i + 1, m->history.commands[i]);
		i++;
	}
	return (0);
}

void	free_t_history(t_m *m)
{
	int	i;

	i = 0;
	while (m->history.count > i)
	{
		free(m->history.commands[i]);
		i++;
	}
}
