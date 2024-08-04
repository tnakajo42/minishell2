/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:12:47 by cadenegr          #+#    #+#             */
/*   Updated: 2024/07/30 12:36:15 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	simu_read_access(t_p *p, t_m *m)
{
	int	i;

	i = 0;
	while (p->cmd_arg[++i])
	{
		if (access(p->cmd_arg[i], F_OK | R_OK) == 0)
			return (4242);
		else
		{
			m->in.exit_status = 1;
			return (0);
		}
	}
	return (0);
}

int	simu_ft_access(char *cmd, t_p *p, t_m *m)
{
	int	i;

	i = -1;
	while (p->path_parts[++i])
	{
		p->path = ft_strjoin(p->path_parts[i], "/");
		p->exec_cmd = ft_strjoin(p->path, cmd);
		free (p->path);
		p->path = NULL;
		if (access(p->exec_cmd, F_OK | X_OK) == 0)
		{
			ft_free_arr (p->path_parts);
			free (p->exec_cmd);
			m->in.exit_status = 0;
			if (p->cmd_arg[1])
				simu_read_access(p, m);
			ft_free_arr (p->cmd_arg);
			return (4242);
		}
		free (p->exec_cmd);
		p->exec_cmd = NULL;
	}
	ft_free_arr (p->cmd_arg);
	ft_free_arr (p->path_parts);
	return (0);
}

int	simu_which_path(char *cmd, char **env, t_p *p, t_m *m)
{
	int	path_len;

	path_len = ft_strlen(env[p->path_position]);
	p->path = ft_substr (env[p->path_position], 5, path_len - 5);
	p->path_parts = ft_split (p->path, ':');
	if (p->path == NULL && p->path_parts == NULL)
		return (0);
	free (p->path);
	p->path = NULL;
	if (simu_ft_access(cmd, p, m) == 0)
	{
		m->in.exit_status = 127;
		return (0);
	}
	(void)m;
	return (1);
}

int	simu_exec_wout_execute(char *cmd, char **env, t_m *m, t_p *p)
{
	char	*command;
	int		len_cmd;

	if (!correct_argument(env, p))
		return (0);
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return (1);
	len_cmd = get_index(cmd, ' ');
	if (len_cmd > 0)
		command = ft_strndup(cmd, len_cmd);
	else
		command = ft_strndup(cmd, ft_strlen(cmd));
	p->cmd_arg = ft_split(cmd, ' ');
	if (!simu_which_path (command, env, p, m))
		len_cmd = 0;
	free (command);
	len_cmd = 1;
	return (len_cmd);
}
