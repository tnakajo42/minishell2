/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:11:25 by cadenegr          #+#    #+#             */
/*   Updated: 2024/07/30 12:11:27 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	termcap_fts(int col, int row)
{
	initialize_terminal();
	clear_screen_t();
	move_cursor(col, row);
	print_terminal_size();
}

void	initialize_terminal(void)
{
	char	term_buffer[2048];

	if (tgetent(term_buffer, getenv("TERM")) < 0)
	{
		fprintf(stderr, "Could not access the termcap database\n");
		exit(1);
	}
}

void	clear_screen_t(void)
{
	char	*cl;

	cl = tgetstr("cl", NULL);
	if (cl)
		tputs(cl, 1, putchar);
}

void	move_cursor(int col, int row)
{
	char	*cm;
	char	*move;

	cm = tgetstr("cm", NULL);
	if (cm)
	{
		move = tgoto(cm, col, row);
		tputs(move, 1, putchar);
	}
}

void	print_terminal_size(void)
{
	struct winsize	ws;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0)
		printf("Terminal size: %d rows, %d columns\n", ws.ws_row, ws.ws_col);
	else
		perror("ioctl");
}
