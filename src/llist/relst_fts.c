/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relst_fts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakajo <tnakajo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:40:07 by tnakajo           #+#    #+#             */
/*   Updated: 2024/07/30 11:40:09 by tnakajo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	c_remove(t_list *curr, t_list *next, t_list *prev, int (*cmp)(void *))
{
	while (curr)
	{
		if (cmp(curr->content))
		{
			next = curr->next;
			ft_lstdelone(curr, free);
			prev->next = next;
			curr = next;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}

void	ft_lstremove_if(t_list **lst, int (*cmp)(void *))
{
	t_list	*current;
	t_list	*previous;
	t_list	*next;

	if (!lst || !*lst)
		return ;
	while (*lst && cmp((*lst)->content))
	{
		next = (*lst)->next;
		ft_lstdelone(*lst, free);
		*lst = next;
	}
	previous = *lst;
	if (previous)
		current = previous->next;
	else
		current = NULL;
	c_remove(current, next, previous, cmp);
}

int	is_empty(void *content)
{
	return (content == NULL || *((char *)content) == '\0');
}

void	del(void *content)
{
	free(content);
}
