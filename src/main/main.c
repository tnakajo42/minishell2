/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakajo <tnakajo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:11:19 by tnakajo           #+#    #+#             */
/*   Updated: 2024/08/01 20:49:58 by tnakajo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	save_env(t_m *m, char **env)
{
	int		i;
	char	*line;

	line = NULL;
	i = -1;
	while (env[++i])
	{
		line = ft_strdup(env[i]);
		ft_lstadd_back(&m->lenv, ft_lstnew(line));
	}
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_m		m;

	(void)av;
	if (ac != 1)
		return (EXIT_FAILURE);
	init_file_names(&m);
	path_env(env, &m);
	simple_prompt_display(&m);
	return (m.in.exit_status);
}
