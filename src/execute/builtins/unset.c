/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakajo <tnakajo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:13:38 by tnakajo           #+#    #+#             */
/*   Updated: 2024/07/30 11:13:39 by tnakajo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_node(void *content)
{
	free(content);
	return ;
}

int	ft_unsetenv(t_m *m, char *name, int l)
{
	t_list	*t_temp;
	t_list	*prev;
	char	name_env[MAX_ENV_NAME];

	t_temp = m->lenv;
	prev = NULL;
	while (t_temp)
	{
		ft_strncpy(name_env, t_temp->content, l);
		name_env[l] = '\0';
		if (!ft_strcmp(name, name_env) && (((char *)t_temp->content)[l] == '=' \
		|| ((char *)t_temp->content)[l] == '\0'))
		{
			if (prev)
				prev->next = t_temp->next;
			else
				m->lenv = t_temp->next;
			ft_lstdelone(t_temp, unset_node);
			return (0);
		}
		prev = t_temp;
		t_temp = t_temp->next;
	}
	return (1);
}

int	unset_cmd(char *str, t_m *m)
{
	char	*command;
	int		command_len;

	if (!ft_strcmp(ft_strchr(str, ' '), " "))
		return (0);
	command = ft_strtrim(str, "unset");
	ft_strtrim_noret(command, " ");
	command_len = ft_strlen(command);
	ft_unsetenv(m, command, command_len);
	free(command);
	m->in.exit_status = 0;
	return (0);
}

/*
please keep the program below
this is for memory leaks in old t_list,
but it may be needed for check valgrind

void	unset_node(void *content)
{
    printf("Success to unset: %s\n", (char *)content);
}

int	ft_unsetenv(t_m *m, char *name, int l)
{
	t_list	*t_temp;
	t_list	*prev;
	char	name_env[MAX_ENV_NAME];

	t_temp = m->lenv;
	prev = NULL;
	while (t_temp)
	{
		ft_strncpy(name_env, t_temp->content, l);
		name_env[l] = '\0';
		if (!ft_strcmp(name, name_env) && (((char *)t_temp->content)[l] == '=' \
		|| ((char *)t_temp->content)[l] == '\0'))
		{
			if (prev)
				prev->next = t_temp->next;
			else
				m->lenv = t_temp->next;
			// free(t_temp->content);
			// free(t_temp);
			ft_lstdelone(t_temp, unset_node);
			return (0);
		}
		prev = t_temp;
		t_temp = t_temp->next;
	}
	return (1);
}

int	unset_cmd(char *str, t_m *m)
{
	char	*command;
	int		command_len;

	if (!ft_strcmp(ft_strchr(str, ' '), " "))
		return (0);
	command = ft_strtrim(str, "unset  ");
	command_len = ft_strlen(command);
	ft_unsetenv(m, command, command_len);
	m->in.exit_status = 0;
	return (0);
}
*/
