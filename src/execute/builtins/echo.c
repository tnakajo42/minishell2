/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:13:21 by tnakajo           #+#    #+#             */
/*   Updated: 2024/08/02 16:32:53 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_dollar_data_len(char *str, int i)
{
	int	n;

	n = 0;
	while (str[i] != ' ' && str[i] != '\0' && str[i] != '\n' && str[i] != '\'' \
		&& str[i] != '>' && str[i] != '<' && str[i] != '|' && str[i] != '"' \
		&& str[i] != '@' && str[i] != '#' && str[i] != '$' && str[i] != '%' \
		&& str[i] != '^' && str[i] != '&' && str[i] != '*' && str[i] != '(' \
		&& str[i] != ')' && str[i] != '-' && str[i] != '+' && str[i] != '{' \
		&& str[i] != '}' && str[i] != '!' && str[i] != '=' && str[i] != '[' \
		&& str[i] != ']' && str[i] != ';' && str[i] != ':' && str[i] != '?' \
		&& str[i] != '/' && str[i] != ',' && str[i] != '.' && str[i] != '~' \
		&& str[i] != '\t' && str[i] != '\b' && str[i] != '\v' && str[i] != '\r')
	{
		n++;
		i++;
	}
	return (n);
}

int	get_dollar_data(char *dest, char *str, int i)
{
	int		j;
	int		n;
	char	*ptr_dest;
	char	*ptr_src;

	j = 0;
	n = get_dollar_data_len(str, i);
	ptr_dest = dest;
	ptr_src = str;
	while (j < n)
	{
		ptr_dest[j] = ptr_src[i];
		i++;
		j++;
	}
	ptr_dest[j] = '\0';
	return (n);
}

int	echo_cmd_print(char *str, t_m *m, int i)
{
	char	*dest;

	if (m->in.back_slash_flag == 0 && str[i] == '$' && str[i + 1] == '?')
	{
		i++;
		printf("%d", m->in.exit_status);
	}
	else if (m->in.back_slash_flag == 0 && str[i] == '$' \
		&& str[i + 1] != '\0' && str[i + 1] != ' ' && str[i + 1] != '\'')
	{
		i++;
		dest = (char *)malloc(sizeof(char) * (get_dollar_data_len(str, i) + 1));
		i += get_dollar_data(dest, str, i) - 1;
		m->history.last_exit_status = show_dollar_data(dest, m, -1);
		free (dest);
	}
	else
	{
		m->in.back_slash_flag = 0;
		printf("%c", str[i]);
	}
	return (i);
}

int	echo_cmd(char *str, t_m *m, int i)
{
	int		n_flag;

	n_flag = 0;
	if (str[i] != ' ')
		return (0);
	if (str[ft_strlen(str) - 1] == ' ')
		str[ft_strlen(str) - 1] = '\0';
	if (str[i + 1] == '-' && str[i + 2] == 'n' && \
		(str[i + 3] == ' ' || str[i + 3] == '\0'))
	{
		n_flag = 1;
		i += 3;
	}
	while (str[++i])
	{
		if (m->in.back_slash_flag == 0 && str[i] == '\\')
			m->in.back_slash_flag = 1;
		else
			i = echo_cmd_print(str, m, i);
	}
	if (n_flag == 0)
		printf("\n");
	m->in.exit_status = 0;
	return (0);
}

/*
int	erase_two_more_spaces(char *str, int i)
{
	while (str[i] == ' ' && str[i + 1] == ' ')
		i++;
	return (i);
}
*/
