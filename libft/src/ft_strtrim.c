/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:32:51 by cadenegr          #+#    #+#             */
/*   Updated: 2024/07/27 08:19:24 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*str;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_strrchr(set, s1[end - 1]))
		end--;
	str = ft_substr(s1, start, end - start);
	return (str);
}

void	ft_strtrim_noret(char *s1, const char *set)
{
	size_t	start;
	size_t	end;
	size_t	len;

	if (s1 == NULL || set == NULL)
		return ;
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_strrchr(set, s1[end - 1]))
		end--;
	len = end - start;
	if (start > 0)
		ft_memmove(s1, s1 + start, len);
	s1[len] = '\0';
}
	// while (s1[end] != s1[start] && ft_strrchr(set, s1[end]))
	// 	end--;
	// str = ft_substr(s1, start, end - start + 1);
/*
#include <stdio.h>
int	main()
{
	char *str;

	str = ft_strtrim("Hola", "Mandol");
	printf("%s\n", str);
	return (0);
}
*/
