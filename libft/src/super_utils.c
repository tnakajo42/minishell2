/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   super_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:19:05 by cadenegr          #+#    #+#             */
/*   Updated: 2024/08/02 16:26:37 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	super_ft_access(char *cmd, t_p *p)
{
	int	i;

	i = 0;
	while (p->path_parts[i])
	{
		p->path = ft_strjoin(p->path_parts[i], "/");
		p->exec_cmd = ft_strjoin(p->path, cmd);
		free (p->path);
		p->path = NULL;
		if (access(p->exec_cmd, F_OK | X_OK) == 0)
		{
			ft_free_arr (p->path_parts);
			return (1);
		}
		free (p->exec_cmd);
		p->exec_cmd = NULL;
		i++;
	}
	ft_free_arr (p->cmd_arg);
	ft_free_arr (p->path_parts);
	return (0);
}

int	super_which_path(char *cmd, char **env, t_p *p)
{
	int	path_len;

	path_len = ft_strlen(env[p->path_position]);
	p->path = ft_substr (env[p->path_position], 5, path_len - 5);
	p->path_parts = ft_split (p->path, ':');
	if (p->path == NULL && p->path_parts == NULL)
		return (0);
	free (p->path);
	p->path = NULL;
	if (!super_ft_access(cmd, p))
		return (0);
	return (1);
}

int	super_exec_wout_execute(char *cmd, char **env, t_p *p)
{
	char	*command;
	int		len_cmd;

	len_cmd = get_index(cmd, ' ');
	if (len_cmd > 0)
		command = ft_strndup(cmd, len_cmd);
	else
		command = ft_strndup(cmd, ft_strlen(cmd));
	p->cmd_arg = ft_split(cmd, ' ');
	if (!super_which_path (command, env, p))
	{
		is_error(6, command);
		return (0);
	}
	free (command);
	return (1);
}

int	super_execute(char *cmd, char **env, t_p *p)
{
	char	*command;
	int		len_cmd;

	len_cmd = get_index(cmd, ' ');
	if (len_cmd > 0)
		command = ft_strndup(cmd, len_cmd);
	else
		command = ft_strndup(cmd, ft_strlen(cmd));
	p->cmd_arg = ft_split(cmd, ' ');
	if (!p->cmd_arg)
	{
		free (command);
		return (1);
	}
	if (!super_which_path (command, env, p))
	{
		is_error(6, "command");
		free (command);
		return (127);
	}
	free (command);
	if (execve (p->exec_cmd, p->cmd_arg, env) == -1)
		return (0);
	return (1);
}
