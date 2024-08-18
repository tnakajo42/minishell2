/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njn0te <njn0te@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 21:41:50 by tnakajo           #+#    #+#             */
/*   Updated: 2024/08/04 19:45:22 by njn0te           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int	g_temp;

void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_temp = 130;
	}
}

void	ctrl_signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
	}
	else if (signal == SIGQUIT)
	{
		printf("\n");
		rl_on_new_line();
	}
	return ;
}

void	set_signal_handlers(t_m *m)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	if (m->in.exit_status == 130)
		m->in.exit_status = 0;
}

void	set_ctrl_signal_handlers(t_m *m)
{
	signal(SIGINT, ctrl_signal_handler);
	signal(SIGQUIT, ctrl_signal_handler);
	if (g_temp == 130)
	{
		m->in.exit_status = g_temp;
		g_temp = 0;
	}
}
