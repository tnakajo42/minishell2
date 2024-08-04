/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:13:27 by cadenegr          #+#    #+#             */
/*   Updated: 2024/07/31 12:10:55 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	path_env(char **env, t_m *m)
{
	int		i;
	int		pwd_len;
	char	*environ;

	pwd_len = ft_strlen("PWD=");
	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PWD=", pwd_len) == 0)
		{
			m->home_position = i;
			break ;
		}
	}
	i = ft_strlen(env[m->home_position]);
	m->pwd = NULL;
	m->pwd = ft_substr (env[m->home_position], pwd_len, i - pwd_len);
	environ = ft_strjoin(m->pwd, "/op_files/env");
	m->files[0] = ft_strdup(environ);
	free (environ);
	save_env(m, env);
	return (1);
}

int	path_input(t_m *m)
{
	char	*in;

	in = ft_strjoin(m->pwd, "/op_files/input");
	m->files[1] = ft_strdup(in);
	free (in);
	save_in_file_trunc(NULL, m->files[1]);
	return (1);
}

int	path_visualizer(t_m *m)
{
	char	*visual;

	visual = ft_strjoin(m->pwd, "/op_files/visualizer");
	m->files[2] = ft_strdup(visual);
	free (visual);
	save_in_file_trunc(NULL, m->files[2]);
	return (1);
}

int	path_checkout(t_m *m)
{
	char	*check;

	check = ft_strjoin(m->pwd, "/op_files/checkout");
	m->files[3] = ft_strdup(check);
	free (check);
	save_in_file_trunc(NULL, m->files[3]);
	return (1);
}
