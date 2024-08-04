/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:49:21 by tnakajo           #+#    #+#             */
/*   Updated: 2024/08/01 12:28:49 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	extract_alpha(const char *line, t_m *m)
{
	int		i;
	char	*extract;

	i = 0;
	while (line[i] && ft_isprint(line[i]) && !ft_isquotes(line[i]))
	{
		if (ft_ispipe(line[i]) || ft_isredirection(line[i]))
			break ;
		i++;
	}
	extract = ft_strtrim_start(line, i);
	return (ft_continue_quotes_travel(line, extract, i, m));
}

void	ft_insert_char_in_str(char *str, char ch, int position)
{
	int	len;
	int	i;

	len = strlen(str);
	if (position < 0 || position > len)
	{
		printf("Invalid position\n");
		return ;
	}
	i = len;
	while (i >= position)
	{
		str[i + 1] = str[i];
		i--;
	}
	str[position] = ch;
	str[len + 1] = '\0';
}
