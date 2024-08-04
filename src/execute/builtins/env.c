/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakajo <tnakajo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:13:24 by tnakajo           #+#    #+#             */
/*   Updated: 2024/07/30 11:13:25 by tnakajo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_env(void *content)
{
	char	*after_equal_str;
	char	*str;

	str = (char *)content;
	after_equal_str = ft_strchr(str, '=');
	if (after_equal_str)
		printf("%s\n", str);
}

int	env_cmd(char *str, t_m *m)
{
	if (ft_strcmp(str, "env "))
	{
		printf("please no argument with env.\n");
		m->in.exit_status = 127;
		return (127);
	}
	ft_lstiter(m->lenv, ft_print_env);
	m->in.exit_status = 0;
	return (1);
}
