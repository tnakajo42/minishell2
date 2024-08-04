/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_sub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:15:01 by tnakajo           #+#    #+#             */
/*   Updated: 2024/08/02 12:58:02 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(t_m *m, char *name)
{
	t_list	*current;
	char	*env_name;
	char	*env_value;
	char	*equal_sign;

	current = m->lenv;
	while (current)
	{
		equal_sign = ft_strchr((char *)current->content, '=');
		if (equal_sign)
		{
			env_name = ft_strndup((char *)current->content, \
				equal_sign - (char *)current->content);
			if (ft_strcmp(env_name, name) == 0)
			{
				env_value = ft_strdup(equal_sign + 1);
				free(env_name);
				return (env_value);
			}
			free(env_name);
		}
		current = current->next;
	}
	return (NULL);
}

int	show_dollar_data(char *content, t_m *m, int fd)
{
	char	*env_value;

	env_value = ft_getenv(m, content);
	if (env_value && fd == -1)
	{
		printf("%s", env_value);
		free(env_value);
		return (-1);
	}
	else if (env_value && fd != -1)
	{
		ft_putstr_fd(env_value, fd);
		free (env_value);
		m->dollar_str = 0;
		return (1);
	}
	return (1);
}
