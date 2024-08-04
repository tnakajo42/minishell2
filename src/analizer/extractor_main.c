/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractor_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:10:53 by cadenegr          #+#    #+#             */
/*   Updated: 2024/07/30 12:10:56 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	path_outcome_results(t_m *m)
{
	char	*outcome;
	char	*results;

	outcome = ft_strjoin(m->pwd, "/op_files/outcome");
	m->files[4] = ft_strdup(outcome);
	free (outcome);
	results = ft_strjoin(m->pwd, "/op_files/results");
	m->files[5] = ft_strdup(results);
	free (results);
	return (1);
}

int	one_checkout_maker(char *input, char **env, t_m *m)
{
	int		fd;
	char	*str;

	fd = open(m->files[3], O_RDONLY);
	add_t_history(m, input);
	if (fd == -1)
		return (0);
	str = get_next_line(fd);
	if (ft_strncmp(str, "command\n", ft_strlen(str)))
		return (0);
	free (str);
	str = get_next_line(fd);
	if (ft_strncmp(str, "pipe\n", ft_strlen(str)) == 0)
		enter_pipes(m, input, env);
	else
		right_redirections(m, input, env);
	free(str);
	close(fd);
	return (1);
}

int	find_type_pipe(char *cmd2)
{
	int	type;

	type = 0;
	if (!ft_strcmp(cmd2, "|"))
		type = 1;
	if (!ft_strcmp(cmd2, "||"))
		type = 2;
	return (type);
}

int	enter_pipes(t_m *m, char *input, char **env)
{
	int		fd;
	int		type;
	char	*cmd;
	char	*cmd2;

	fd = open(m->files[2], O_RDONLY);
	add_t_history(m, input);
	cmd = extract_line(fd);
	cmd2 = extract_line(fd);
	type = find_type_pipe(cmd2);
	free (cmd2);
	cmd2 = extract_line(fd);
	if (type == 1)
		pipex(cmd, cmd2, env, &m->in.exit_status);
	free(cmd);
	free(cmd2);
	close(fd);
	return (1);
}

int	ft_extractor(char *line, t_m *m)
{
	if (ft_iswhitespace(line[0]))
		extract_whitespace(line, m);
	else if (line[0] == 39)
		extract_single_q(line, m);
	else if (line[0] == 34)
		extract_double_q(line, m);
	else if (ft_isprint(line[0]) && line[0] != '$')
		extract_printable(line, m);
	else if (line[0] == '$')
		extract_moneysign(line, m);
	else
		return (0);
	return (1);
}
