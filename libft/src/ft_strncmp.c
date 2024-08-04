/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:35:23 by cadenegr          #+#    #+#             */
/*   Updated: 2024/07/11 10:40:31 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while ((s1[i] || s2[i]) && (i < n))
	{
		if ((unsigned char)s1[i] < (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		if ((unsigned char)s1[i] > (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

/*
#include <stdio.h>
#include <string.h>
int	main()
{
	char	first[] = "Hello";
	char	second[] = "Helyb";

	printf ("%d\n", strncmp(first, second,0));
	printf ("%d\n", ft_strncmp(first, second, 0));
	printf ("%d\n", strncmp(first, second, 1));
	printf ("%d\n", ft_strncmp(first, second, 1));
	printf ("%d\n", strncmp(first, second, 2));
	printf ("%d\n", ft_strncmp(first, second, 2));
	printf ("%d\n", strncmp(first, second, 3));
	printf ("%d\n", ft_strncmp(first, second, 3));
	printf ("%d\n", strncmp(first, second, 4));
	printf ("%d\n", ft_strncmp(first, second, 4));
	printf ("%d\n", strncmp(first, second, 5));
	printf ("%d\n", ft_strncmp(first, second, 5));
	printf ("%d\n", strncmp(first, second, 6));
	printf ("%d\n", ft_strncmp(first, second, 6));

    char    first1[] = "Helloa";
    char    second1[] = "Helloz";

    printf("\n%d", strncmp(first1, second1, 6));
    printf("\n%d", ft_strncmp(first1, second1, 6));
	return(0);
}
// gcc libft/src/ft_strncmp.c include/libft.h && ./a.out && rm ./a.out 
*/
