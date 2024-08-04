/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   super_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 12:17:16 by cadenegr          #+#    #+#             */
/*   Updated: 2024/07/26 20:31:04 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	super_read(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit (EXIT_FAILURE);
	dup2 (fd, STDIN_FILENO);
	close (fd);
}

void	super_append(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		exit (EXIT_FAILURE);
	dup2 (fd, STDOUT_FILENO);
	close (fd);
}

void	super_trunc(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit (EXIT_FAILURE);
	dup2 (fd, STDOUT_FILENO);
	close (fd);
}

void	super_delimiter(char *delimit, int fd_out)
{
	char	*input;
	char	*output;

	input = NULL;
	output = NULL;
	while (1)
	{
		input = readline("heredoc>");
		if (input == NULL || !input || ft_strcmp(input, delimit) == 0)
			break ;
		input = ft_strjoin_gnl(input, "\n");
		output = ft_strjoin_gnl(output, input);
		if (input)
			free (input);
	}
	ft_putstr_fd(output, fd_out);
	if (input)
		free (input);
	if (output)
		free (output);
	close (fd_out);
	exit(EXIT_SUCCESS);
}

void	super_pipes(t_p *p)
{
	if (p->i > 0)
	{
		close(p->fd[(p->i - 1) * 2 + 1]);
		dup2(p->fd[(p->i - 1) * 2], STDIN_FILENO);
	}
	if (p->i < p->n_cmds - 1)
	{
		close(p->fd[p->i * 2]);
		dup2(p->fd[p->i * 2 + 1], STDOUT_FILENO);
	}
}
