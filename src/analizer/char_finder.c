/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:09:46 by cadenegr          #+#    #+#             */
/*   Updated: 2024/07/30 12:09:48 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ' and "
int	ft_isquotes(int c)
{
	if (c == 39)
		return (1);
	if (c == 34)
		return (2);
	return (0);
}

//'|'
int	ft_ispipe(int c)
{
	return (c == 124);
}

//'>', '<'
int	ft_isredirection(int c)
{
	if (c == 62)
		return (1);
	if (c == 60)
		return (2);
	return (0);
}

// '\', ';', '$', '?', '&'
int	ft_isspecialsign(int c)
{
	if (c == 92)
		return (1);
	if (c == 59)
		return (2);
	if (c == 36)
		return (3);
	if (c == 63)
		return (4);
	if (c == 38)
		return (5);
	return (0);
}

// '\t', '\n', '\v', '\f', '\r' and space
int	ft_iswhitespace(int c)
{
	if (c >= 9 && c <= 13)
		return (1);
	if (c == 32)
		return (1);
	return (0);
}
