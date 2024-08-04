/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakajo <tnakajo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:13:36 by tnakajo           #+#    #+#             */
/*   Updated: 2024/07/30 11:13:36 by tnakajo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_cmd(char *str, t_m *m)
{
	char	cwd[MAX_PATH_SIZE];

	(void)str;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		printf("getcwd() error\n");
	m->in.exit_status = 0;
	return (1);
}
