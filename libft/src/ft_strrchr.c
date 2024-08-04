/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:35:54 by cadenegr          #+#    #+#             */
/*   Updated: 2024/07/18 12:35:57 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	last;

	i = 0;
	last = -1;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			last = i;
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	if (last != -1)
		return ((char *)&s[last]);
	return (0);
}

int	get_index_reverse(const char *s, char c)
{
	char	*ptr;

	ptr = ft_strrchr(s, c);
	if (ptr == NULL)
		return (-1);
	return ((int)(ptr - s));
}

/*
#include <stdio.h>
int	main()
{
	char *str = "Hello my little friend!";
	char *ptr;

	ptr = ft_strrchr(str, 'f');
	printf("ptr: %s\n", ptr);
	return (0);
}*/
