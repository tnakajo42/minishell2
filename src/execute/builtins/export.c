/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakajo <tnakajo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:13:33 by tnakajo           #+#    #+#             */
/*   Updated: 2024/07/30 11:13:34 by tnakajo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_export(void *content)
{
	char	name[MAX_ENV_NAME];
	char	value[MAX_ENV_VALUE];
	char	*after_equal_str;
	char	*str;
	t_len	t_len;

	str = (char *)content;
	after_equal_str = ft_strchr(str, '=');
	t_len.name_len = after_equal_str - str;
	if (after_equal_str == NULL)
		value[0] = '\0';
	else
	{
		t_len.value_len = ft_strlen(after_equal_str);
		ft_strncpy_for_export_name(value, after_equal_str, t_len.value_len);
		t_len.name_len++;
	}
	ft_strncpy_for_export_name(name, str, t_len.name_len);
	if (value[0] != '\0')
		printf("declare -x %s=\"%s\"\n", name, value);
	else if (after_equal_str)
		printf("declare -x %s=\"\"\n", name);
	else
		printf("declare -x %s\n", name);
}

int	export_no_args(t_m *m)
{
	ft_lstiter(m->lenv, ft_print_export);
	return (0);
}

int	ft_updateenv(t_m *m, char *name, const char *new_content)
{
	t_list	*t_temp;
	int		len;
	char	name_env[MAX_ENV_NAME];

	t_temp = m->lenv;
	while (t_temp)
	{
		if (ft_strchr(t_temp->content, '=') == NULL)
			len = ft_strlen((char *)t_temp->content);
		else
			len = ft_strchr(t_temp->content, '=') - (char *)t_temp->content;
		ft_memmove(name_env, t_temp->content, len);
		name_env[len] = '\0';
		if (!ft_strcmp(name, name_env))
		{
			if (new_content[len] == '=')
			{
				free(t_temp->content);
				t_temp->content = ft_strdup(new_content);
			}
			return (1);
		}
		t_temp = t_temp->next;
	}
	return (0);
}

int	ft_setenv(char *name, char *value, t_m *m, char *command)
{
	char	*temp;
	int		overwrite;

	if (ft_isspace(name) || ft_isspace(value))
	{
		m->in.exit_status = 1;
		printf("no space please\n");
		return (1);
	}
	temp = ft_strdup(command);
	if (!temp)
	{
		m->in.exit_status = 1;
		printf("ft_strdup error\n");
		return (1);
	}
	overwrite = ft_updateenv(m, name, temp);
	if (overwrite == 0)
		ft_lstadd_back(&m->lenv, ft_lstnew(temp));
	else
		free(temp);
	free (command);
	return (0);
}

int	export_cmd(char *str, t_m *m)
{
	char	name[MAX_ENV_NAME];
	char	value[MAX_ENV_VALUE];
	char	*after_equal_str;
	char	*command;
	t_len	t_len;

	m->in.exit_status = 0;
	if (!ft_strcmp(ft_strchr(str, ' '), " "))
		return (export_no_args(m));
	command = ft_strtrim(ft_strchr(str, ' '), " ");
	after_equal_str = ft_strchr(command, '=');
	t_len.name_len = after_equal_str - command;
	if (after_equal_str == NULL)
		value[0] = '\0';
	else
	{
		t_len.value_len = ft_strlen(after_equal_str);
		ft_strncpy_for_export_name(value, after_equal_str, t_len.value_len);
		t_len.name_len++;
	}
	ft_strncpy_for_export_name(name, command, t_len.name_len);
	return (ft_setenv(name, value, m, command));
}
