/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 14:13:29 by ighannam          #+#    #+#             */
/*   Updated: 2025/07/31 14:15:00 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	cc;
	size_t			i;
	unsigned char	*ss;

	ss = (unsigned char *)s;
	cc = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		*(char *)s = cc;
		s++;
		i++;
	}
	return (ss);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*result;

	if (nmemb == 0 || size == 0)
	{
		result = malloc(1);
		if (!result)
			return (NULL);
		ft_memset(result, 0, 1);
		return (result);
	}
	if (nmemb > (size_t)(-1) / size)
		return (NULL);
	result = malloc(nmemb * size);
	if (!result)
		return (NULL);
	ft_memset(result, 0, nmemb * size);
	return (result);
}

char	*ft_strchr(const char *s, int c)
{
	char	*s_return;

	if (!s)
		return (NULL);
	s_return = (char *)s;
	while (*s_return != '\0')
	{
		if (*s_return == (unsigned char)c)
			return (s_return);
		s_return++;
	}
	if (c == 0)
		return (s_return);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	size;

	size = 0;
	while (s && s[size] != '\0')
		size++;
	return (size);
}
