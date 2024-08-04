/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:42:47 by cadenegr          #+#    #+#             */
/*   Updated: 2024/07/08 12:27:01 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//here I made it to > than 32, before it was wrong!!!!
int	ft_isprint(int c)
{
	return (c > 32 && c <= 126);
}

/*
int main()
{
	int n = ft_isprint("\f");
	printf ("%d\n", n);
	return(0);
}*/
