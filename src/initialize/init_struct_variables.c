/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_variables.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:14:05 by cadenegr          #+#    #+#             */
/*   Updated: 2024/08/02 11:58:45 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_file_names(t_m *m)
{
	m->files = malloc (sizeof(char *) * 5);
	m->files[0] = NULL;
	m->files[1] = NULL;
	m->files[2] = NULL;
	m->files[3] = NULL;
	m->files[4] = NULL;
	m->lenv = NULL;
	return (1);
}

int	init_struct_input_2(t_m *m)
{
	m->in.from_double = 0;
	m->in.out_double = true;
	m->in.split = NULL;
	m->in.back_slash_flag = 0;
	m->lst = NULL;
	m->cmds = NULL;
	m->i = 0;
	m->checkout = NULL;
	m->what_is = false;
	m->is_echo = false;
	m->dollar_str = 0;
	return (1);
}

int	init_struct_input(t_m *m)
{
	m->in.is_alnum = 0;
	m->in.nested_single = 0;
	m->in.nested_double = 0;
	m->in.input_len = 0;
	m->in.single_q = 0;
	m->in.double_q = 0;
	m->in.quoted_words = 0;
	m->in.right_d = 0;
	m->in.left_d = 0;
	m->in.slash = 0;
	m->in.semicolon = 0;
	m->in.dollar = 0;
	m->in.question = 0;
	m->in.andsign = 0;
	m->in.is_pipe = 0;
	m->in.is_whitespc = 0;
	init_struct_input_2(m);
	return (1);
}

void	init_t_history(t_m *m)
{
	m->history.count = 0;
	m->history.current_history_index = 0;
	m->break_flag = 0;
	m->ctrld_firstrun = true;
}

	// path_outcome_results(m);
void	init_before_display(t_m *m)
{
	m->in.exit_status = 0;
	m->env = NULL;
	m->history.last_exit_status = 0;
	path_input(m);
	path_visualizer(m);
	path_checkout(m);
	init_t_history(m);
}
