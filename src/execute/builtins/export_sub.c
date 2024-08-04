/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakajo <tnakajo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:13:30 by tnakajo           #+#    #+#             */
/*   Updated: 2024/07/30 11:13:31 by tnakajo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (1);
	while (s[i] != '\0')
	{
		if ((s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || \
			s[i] == '\v' || s[i] == '\f' || s[i] == '\r'))
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strncpy_for_export_name(char *dest, char *src, unsigned int n)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (src[j] == '=')
		j++;
	while (src[j] != '\0' && i < n - 1)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}
