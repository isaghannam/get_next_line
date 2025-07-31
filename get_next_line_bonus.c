/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 14:13:00 by ighannam          #+#    #+#             */
/*   Updated: 2025/07/31 16:36:53 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoin_free(char *dst, char *src)
{
	int		size_dst;
	char	*joined_str;
	int		i;

	size_dst = (int)ft_strlen(dst);
	i = -1;
	joined_str = ft_calloc((size_dst + (int)ft_strlen(src) + 1), 1);
	if (!joined_str)
	{
		free(src);
		free(dst);
		return (NULL);
	}
	while (++i < size_dst)
		joined_str[i] = dst[i];
	while (i < (int)ft_strlen(src) + size_dst)
	{
		joined_str[i] = src[i - size_dst];
		i++;
	}
	free(src);
	free(dst);
	return (joined_str);
}

char	*ft_extract_line(char *str)
{
	char	*line;
	int		size_line;
	int		i;

	size_line = 0;
	if (!str || str[size_line] == '\0')
	{
		free(str);
		return (NULL);
	}
	while (str[size_line] != '\n' && str[size_line] != '\0')
		size_line++;
	if (str[size_line] == '\n')
		line = ft_calloc(size_line + 2, 1);
	else
		line = ft_calloc(size_line + 1, 1);
	if (!line)
		return (NULL);
	i = -1;
	while (++i < size_line)
		line[i] = str[i];
	if (str[size_line] == '\n')
		line[size_line] = str[size_line];
	return (line);
}

char	*ft_update_leftovers(char *leftovers, char *line)
{
	char	*new_leftovers;
	int		equal_chars;
	int		i;

	if (!leftovers || !line)
	{
		free (line);
		return (NULL);
	}
	equal_chars = 0;
	while (leftovers[equal_chars] == line [equal_chars] && line[equal_chars])
		equal_chars++;
	new_leftovers = ft_calloc(ft_strlen(leftovers + equal_chars) + 1, 1);
	if (leftovers[equal_chars] == '\0' || !new_leftovers)
	{
		free(leftovers);
		if (new_leftovers)
			free(new_leftovers);
		return (NULL);
	}
	i = -1;
	while (leftovers[equal_chars + (++i)] != '\0')
		new_leftovers[i] = leftovers[equal_chars + i];
	free(leftovers);
	return (new_leftovers);
}

void	ft_form_leftovers(char **leftovers, int fd)
{
	ssize_t	bytes_read;
	char	*buffer;

	bytes_read = 1;
	while (ft_strchr(*leftovers, '\n') == NULL && bytes_read > 0)
	{
		buffer = ft_calloc((BUFFER_SIZE + 1), 1);
		if (!buffer)
			return ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			free(*leftovers);
			*leftovers = NULL;
			return ;
		}
		if (!buffer || buffer[0] == '\0')
			free(buffer);
		else
			*leftovers = ft_strjoin_free(*leftovers, buffer);
	}
}

char	*get_next_line(int fd)
{
	static char	*leftovers[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!leftovers[fd])
	{
		leftovers[fd] = ft_calloc(1, 1);
		if (!leftovers[fd])
			return (NULL);
	}
	ft_form_leftovers(&(leftovers[fd]), fd);
	line = ft_extract_line(leftovers[fd]);
	leftovers[fd] = ft_update_leftovers(leftovers[fd], line);
	if (!line || line[0] == '\0')
		free (leftovers[fd]);
	return (line);
}
