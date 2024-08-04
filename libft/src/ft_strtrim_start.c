/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_start.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:36:07 by cadenegr          #+#    #+#             */
/*   Updated: 2024/07/27 08:08:02 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strtrim_start_noret(char *s, size_t trim_len)
{
	size_t	s_len;

	if (!s)
		return ;
	s_len = strlen(s);
	if (trim_len >= s_len)
		s[0] = '\0';
	else
		ft_memmove(s, s + trim_len, s_len - trim_len + 1);
}

void	ft_strtrim_end_noret(char *s, size_t trim_len)
{
	size_t	s_len;

	if (!s)
		return ;
	s_len = strlen(s);
	if (trim_len >= s_len)
		s[0] = '\0';
	else
		s[s_len - trim_len] = '\0';
}

char	*ft_strtrim_start(const char *s, size_t trim_len)
{
	char	*trimmed_str;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (trim_len >= s_len)
	{
		trimmed_str = ft_strdup(s);
		((char *)s)[0] = '\0';
	}
	else
	{
		trimmed_str = ft_strndup(s, trim_len);
		ft_memmove((char *)s, s + trim_len, s_len - trim_len + 1);
	}
	return (trimmed_str);
}

char	*ft_strtrim_end(const char *s, size_t trim_len)
{
	char	*trimmed_str;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (trim_len >= s_len)
	{
		trimmed_str = ft_strdup(s);
		((char *)s)[0] = '\0';
	}
	else
	{
		trimmed_str = ft_strndup(s + s_len - trim_len, trim_len);
		((char *)s)[s_len - trim_len] = '\0';
	}
	return (trimmed_str);
}

char	*ft_strtrim_start_nomodify(const char *s, size_t trim_len)
{
	char	*trimmed_str;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (trim_len >= s_len)
	{
		trimmed_str = ft_strdup(s);
		return (trimmed_str);
	}
	else
	{
		trimmed_str = ft_strndup(s, trim_len);
		return (trimmed_str);
	}
}

// char	*ft_strtrim_end_nomodify(char *s, size_t trim_len)
// {
// 	char	*trimmed_str;
// 	size_t	s_len;

// 	if (!s)
// 		return (NULL);
// 	s_len = ft_strlen(s);
// 	if (trim_len >= s_len)
// 	{
// 		trimmed_str = ft_strdup(s);
// 		if (trimmed_str)
// 			s[0] = '\0';
// 	}
// 	else
// 	{
// 		trimmed_str = ft_strndup(s + s_len - trim_len, trim_len);
// 		if (trimmed_str)
// 			s[s_len - trim_len] = '\0';
// 	}
// 	return (trimmed_str);
// }