/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   super_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:22:31 by cadenegr          #+#    #+#             */
/*   Updated: 2024/08/02 16:16:44 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	how_many_pipes(char **cmds, t_p *p)
{
	int	i;

	i = 0;
	while (cmds[i])
		i++;
	p->n_cmds = i;
	p->n_pipes = i - 1;
	p->fd = malloc((sizeof(int) * 2 * (p->n_pipes)));
	p->pid = malloc (sizeof(pid_t) * 2 * p->n_cmds);
	if (!p->fd)
		return (EXIT_FAILURE);
	return (1);
}

char	*get_file_from_command(char *cmd, char *symbol)
{
	char	*file;
	char	*temp;

	file = NULL;
	temp = NULL;
	file = ft_substr(cmd, get_index_reverse(cmd, symbol[0]), ft_strlen(cmd));
	if (file)
		temp = ft_strtrim(file, symbol);
	free (file);
	return (temp);
}

char	*extract_file(char *cmd, char *symbol)
{
	char	*file;

	file = NULL;
	if (ft_strnstr(cmd, symbol, ft_strlen(cmd)))
	{
		file = get_file_from_command(cmd, symbol);
		return (file);
	}
	return (NULL);
}

void	close_wait(t_p *p, int *exit_status)
{
	int	i;
	int	status;

	i = -1;
	while (++i < 2 * (p->n_pipes))
		close (p->fd[i]);
	i = -1;
	while (++i < p->n_cmds)
		waitpid(p->pid[p->i], NULL, 0);
	waitpid(p->pid[p->i], &status, 0);
	if (WIFEXITED(status))
		*exit_status = WEXITSTATUS(status);
}
