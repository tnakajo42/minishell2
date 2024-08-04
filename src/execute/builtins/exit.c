/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakajo <tnakajo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:13:27 by tnakajo           #+#    #+#             */
/*   Updated: 2024/07/30 11:13:28 by tnakajo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_cmd(char *str, t_m *m)
{
	(void)m;
	if (ft_strncmp(str, "exit ", 5) == 0 && ft_strlen(str) == 5)
		return (42);
	printf("NO ARGUMENT PLEASE\n");
	return (1);
}
