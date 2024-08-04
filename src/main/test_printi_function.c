/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_printi_function.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:14:21 by cadenegr          #+#    #+#             */
/*   Updated: 2024/07/30 12:14:24 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_input(char *input)
{
	char	*pos;

	pos = NULL;
	if (input)
	{
		pos = ft_strchr(input, '\r');
		if (pos != NULL)
			*pos = '\0';
	}
	return (input);
}

int	error(char *s)
{
	printf("%s\n", s);
	return (0);
}

void	print_in_dec(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		printf("%d ", str[i]);
	printf("\n");
}

int	p(void *arg, int type)
{
	char	c;
	char	*s;
	int		d;

	if (type == 0)
		return (printf("@@@@----->\n"));
	if (type == 1)
	{
		c = *(char *)arg;
		return (write(1, &c, 1));
	}
	if (type == 2)
	{
		s = (char *)arg;
		return (printf("%s\n", s));
	}
	if (type == 3)
	{
		d = *(int *)arg;
		return (printf("%d\n", d));
	}
	return (0);
}
