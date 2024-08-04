/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:13:16 by tnakajo           #+#    #+#             */
/*   Updated: 2024/08/01 17:44:01 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_update_pwds(t_m *m, char *name, const char *new_content)
{
	t_list	*t_temp;
	int		name_env_len;
	char	name_env[MAX_ENV_NAME];

	t_temp = m->lenv;
	while (t_temp)
	{
		if (ft_strchr(t_temp->content, '=') == NULL)
			name_env_len = ft_strlen((char *)t_temp->content);
		else
			name_env_len = ft_strchr(t_temp->content, '=') - \
			(char *)t_temp->content;
		ft_memmove(name_env, t_temp->content, name_env_len);
		name_env[name_env_len] = '\0';
		if (!ft_strcmp(name, name_env))
		{
			free (t_temp->content);
			if (!ft_strcmp("OLDPWD", name_env) || !ft_strcmp("PWD", name_env))
				t_temp->content = ft_strjoin(name_env, new_content);
		}
		t_temp = t_temp->next;
	}
}

char	*expand_home_directory(char *path)
{
	char			*home_dir;
	char			*expanded_path;

	if (path[0] == '~')
	{
		home_dir = getenv("HOME");
		if (!home_dir)
		{
			printf("Error: HOME environment variable is not set or malloc.\n");
			return (NULL);
		}
		expanded_path = malloc(strlen(home_dir) + strlen(path));
		if (!expanded_path)
		{
			printf("malloc error\n");
			return (NULL);
		}
		ft_strcpy(expanded_path, home_dir);
		ft_strcat(expanded_path, path + 1);
		return (expanded_path);
	}
	return (strdup(path));
}

int	cd_cmd(char *str, t_m *m)
{
	char	path[MAX_PATH_SIZE];
	char	cwd[MAX_PATH_SIZE];
	char	*expanded_path;
	char	*temp;

	temp = ft_strtrim(str, "cd");
	ft_strtrim_noret(temp, " ");
	if (temp[0] == '\0' || ft_strcmp(temp, "~") == 0)
		ft_strcpy(path, "~");
	else
		ft_strcpy(path, temp);
	expanded_path = expand_home_directory(path);
	ft_update_pwds(m, "OLDPWD", getcwd(cwd, sizeof(cwd)));
	if (chdir(expanded_path) != 0)
	{
		printf("CHDIR ERROR\n");
		m->in.exit_status = 1;
	}
	else
		m->in.exit_status = 0;
	ft_update_pwds(m, "PWD", getcwd(cwd, sizeof(cwd)));
	free(expanded_path);
	free (temp);
	return (1);
}

/*
please keep the program below
this is for memory leaks in old t_list,
but it may be needed for check valgrind

#include "minishell.h"

void	unset_node(void *content);

t_list *ft_lstnew_for_pwds(const char *content)
{
	t_list *aux;
	char *content_copy;

	aux = (t_list *)malloc(sizeof(t_list));
	if (!aux)
		return (NULL);
	content_copy = ft_strdup(content);
	if (!content_copy)
	{
		free(aux);
		return (NULL);
	}
	aux->content = content_copy;
	aux->next = NULL;
	return (aux);
}

void	ft_update_pwds(t_m *m, char *name, const char *new_content)
{
	char	temp[MAX_PATH_SIZE];
	int		name_env_len;

	printf("\n--------------------------\n");
	printf("name-->%s<--\nnew_content-->%s<--", name, new_content);
	name_env_len = ft_strlen(name);
	ft_memmove(temp, name, name_env_len);
	temp[name_env_len] = '\0';
	ft_strcat(temp, "=");
	ft_strcat(temp, new_content);
	printf("\ntemp-->%s<--", temp);
	printf("\n--------------------------\n");
	ft_lstadd_back(&m->lenv, ft_lstnew(temp));
}

void	ft_check_pwds(t_m *m, char *name, const char *new_content)
{
	t_list	*t_temp;
	t_list	*prev;
	t_list	*to_delete;
	int		name_env_len;
	char	name_env[MAX_ENV_NAME];

	t_temp = m->lenv;
	prev = NULL;
	while (t_temp)
	{
		if (ft_strchr(t_temp->content, '=') == NULL)
			name_env_len = ft_strlen((char *)t_temp->content);
		else
			name_env_len = ft_strchr(t_temp->content, '=') - (char *)t_temp->content;
		ft_memmove(name_env, t_temp->content, name_env_len);
		name_env[name_env_len] = '\0';
		if (!ft_strcmp(name, name_env))
		{
            to_delete = t_temp;
            t_temp = t_temp->next;
			if (prev)
				prev->next = t_temp;
			else
				m->lenv = t_temp;
            ft_lstdelone(to_delete, unset_node);
			break ;
        }
		prev = t_temp;
		t_temp = t_temp->next;
	}
	ft_update_pwds(m, name, new_content);
}

char	*expand_home_directory(char *path)
{
	char			*home_dir;
	char			*expanded_path;

	if (path[0] == '~')
	{
		home_dir = getenv("HOME");
		if (!home_dir)
		{
			printf("Error: HOME environment variable is not set or malloc.\n");
			return (NULL);
		}
		expanded_path = malloc(strlen(home_dir) + strlen(path));
		if (!expanded_path)
		{
			printf("malloc error\n");
			return (NULL);
		}
		ft_strcpy(expanded_path, home_dir);
		ft_strcat(expanded_path, path + 1);
		return (expanded_path);
	}
	return (strdup(path));
}


int	cd_cmd(char *str, t_m *m)
{
	char	path[MAX_PATH_SIZE];
	char	cwd[MAX_PATH_SIZE];
	char	*expanded_path;

	str = ft_strtrim(str, "cd ");
	if (str[0] == '\0' || ft_strcmp(str, "~") == 0)
		ft_strcpy(path, "~");
	else
		ft_strcpy(path, str);
	expanded_path = expand_home_directory(path);
	ft_check_pwds(m, "OLDPWD", getcwd(cwd, sizeof(cwd)));
	if (chdir(expanded_path) != 0)
	{
		m->in.exit_status = 1;
		printf("CHDIR ERROR\n");
	}
	else
	{
		m->in.exit_status = 0;
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			ft_check_pwds(m, "PWD", cwd);
		else
			printf("Error getting current working directory\n");
	}
	free(expanded_path);
	return (1);
}
*/
