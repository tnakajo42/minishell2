/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njn0te <njn0te@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:45:21 by tnakajo           #+#    #+#             */
/*   Updated: 2024/08/04 19:39:32 by njn0te           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_free(t_m *m)
{
	clear_history();
	free_t_history(m);
	ft_lstclear(&m->lst, del);
	ft_lstclear(&m->lenv, del);
	ft_free_arr(m->env);
	free (m->pwd);
	m->lst = NULL;
}

int	store_env(t_m *m)
{
	t_list	*temp;
	char	*content;
	char	*env_str;

	temp = m->lenv;
	env_str = NULL;
	if (m->env)
		ft_free_arr(m->env);
	save_in_file_trunc(NULL, m->files[0]);
	while (temp)
	{
		content = (char *)temp->content;
		save_in_file_append(content, m->files[0]);
		temp = temp->next;
		env_str = ft_strjoin_gnl(env_str, content);
		env_str = ft_strjoin_gnl(env_str, " ");
	}
	m->env = ft_split(env_str, ' ');
	if (env_str)
		free(env_str);
	ft_lstclear(&temp, del);
	return (1);
}

int	update_input(char *input, t_m *m)
{
	int		index;

	if (input[0] == '\0' || input[0] == '\n')
		return (0);
	if (ft_iswhitespace(input[0]))
	{
		index = 0;
		while (ft_iswhitespace(input[index]))
			index++;
		if (ft_isprint(input[index]))
			input_whitespace(input);
		else
			return (0);
	}
	index = get_index(input, '\n');
	input = ft_strtrim_start(input, index);
	add_history(input);
	save_in_file_append(input, m->files[1]);
	free (input);
	return (1);
}

int	display_processes(char *input, t_m *m)
{
	int		where_to_go;

	m->ctrld_firstrun = false;
	update_input(input, m);
	store_env(m);
	if (!analize(m))
		return (0);
	where_to_go = ft_checkout(m);
	if (where_to_go == 1)
		try_execute(m, input, m->env);
	else if (where_to_go == 3)
		one_checkout_maker(input, m->env, m);
	else if (!m->in.is_pipe && where_to_go > 3)
	{
		checkout_cmds_redirect(where_to_go, m);
		checkout_redirect(where_to_go, input, m->env, m);
	}
	else if (where_to_go > 3)
	{
		checkout_cmds(where_to_go, m);
		checkout_maker(where_to_go, input, m->env, m);
	}
	return (1);
}

void	simple_prompt_display(t_m *m)
{
	char	*input;

	input = NULL;
	init_before_display(m);
	set_signal_handlers(m);
	while (1)
	{
		input = readline("minishell$ ");
		input = get_input(input);
		set_ctrl_signal_handlers(m);
		if (input == NULL)
		{
			printf("exit\n");
			break ;
		}
		display_processes(input, m);
		if (input)
			free (input);
		set_signal_handlers(m);
		if (m->break_flag == 42)
			break ;
	}
	if (!m->ctrld_firstrun)
		minishell_free(m);
	remove_files(m->files);
}
