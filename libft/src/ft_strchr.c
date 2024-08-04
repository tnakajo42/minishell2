/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:28:16 by cadenegr          #+#    #+#             */
/*   Updated: 2024/07/14 16:28:44 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* #include "../../include/libft.h" */

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != (char)c)
		i++;
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (0);
}

int	get_index(const char *s, char c)
{
	char	*ptr;

	ptr = ft_strchr(s, c);
	if (ptr == NULL)
		return (-1);
	return ((int)(ptr - s));
}

/*
#include <stdio.h>
int main()
{
	char *str = "Hello!";
	char *ptr;

	ptr = ft_strchr(str, 'l');
	printf("ptr: %s\n", ptr); // ptr: llo!
	return (0);
}
// gcc libft/src/ft_strchr.c include/libft.h && ./a.out && rm ./a.out 
*/
