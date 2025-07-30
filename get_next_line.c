/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ighannam <ighannam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:59:18 by ighannam          #+#    #+#             */
/*   Updated: 2025/07/30 16:38:22 by ighannam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "get_next_line.h"

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

char	*ft_strjoin_free(char *dst, char *src)
{
	size_t	size_dst;
	size_t	size_src;
	char	*joined_str;
	size_t	i;

	
	size_dst = ft_strlen(dst);
	size_src = ft_strlen(src);
	i = 0;
	joined_str = ft_calloc((size_dst + size_src + 1), 1);
	if (!joined_str)
	{
		free(src);
		free(dst);
		return (NULL);
	}
	while (i < size_dst)
	{
		joined_str[i] = dst[i];
		i++;
	}
	while (i < size_src + size_dst)
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
	size_t	size_line;
	size_t	i;
	
	size_line = 0;
	if (!str || str[size_line] == '\0')
	{
		free(str);
		return(NULL);
	}
	while (str[size_line] != '\n' && str[size_line] != '\0')
		size_line++;
	if (str[size_line] == '\n')
	{
		line = ft_calloc(size_line + 2, 1);
		if (!line)
			return(NULL);
	}	
	else
	{
		line = ft_calloc(size_line + 1, 1);
		if (!line)
			return(NULL);
	}
	i = 0;
	while (i < size_line)
	{
		line[i] = str[i];
		i++;
	}
	if (str[size_line] == '\n')
		line[size_line] = str[size_line];
	return(line);
}

char	*ft_update_leftovers(char *leftovers, char *line)
{
	char	*new_leftovers;
	size_t	num_equal_chars;
	size_t	i;

	if (!leftovers || !line)
	{
		//free (leftovers);
		free (line);
		return (NULL);
	}
	num_equal_chars = 0;
	while (leftovers[num_equal_chars] == line [num_equal_chars] && leftovers[num_equal_chars] && line[num_equal_chars])
		num_equal_chars++;
	if (leftovers[num_equal_chars] == '\0')
	{
		free (leftovers);
		return (NULL);
	}
	new_leftovers = ft_calloc(ft_strlen(leftovers + num_equal_chars) + 1, 1);
	if (!new_leftovers)
	{
		free(leftovers);
		return (NULL);
	}
	i = 0;
	while (leftovers[num_equal_chars + i] != '\0')
	{
		new_leftovers[i] = leftovers[num_equal_chars + i];
		i++;
	}
	free(leftovers);
	return (new_leftovers);
}

char	*get_next_line(int fd)
{
	static char	*leftovers;
	char		*line;
	char		*buffer;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
    	return (NULL);
	if (!leftovers)
	{
		leftovers = ft_calloc(1, 1);
		if (!leftovers)
			return (NULL);
	}
	bytes_read = 1;
	while (ft_strchr(leftovers, '\n') == NULL && bytes_read > 0)
	{
		buffer = ft_calloc((BUFFER_SIZE + 1), 1);
		if (!buffer)
			return (NULL);		
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);			
			return (NULL);
		}
		if (!buffer || buffer[0] == '\0')
		{
			free(buffer);
		}
		else
			leftovers = ft_strjoin_free(leftovers, buffer);
	}
	line = ft_extract_line(leftovers);
	leftovers = ft_update_leftovers(leftovers, line);
	if (!line || line[0] == '\0')
		free (leftovers);
	return (line);
}



// int main()
// {
// 	int fd = open("teste", O_RDONLY);
//     if (fd == -1) {
//         printf("erro ao abrir");
//         return 1;
//     }
	
// 	char *str = get_next_line(fd);
// 	printf("%s", str);
// 	while (str)
// 	{
// 		str = get_next_line(fd);
// 		printf("%s", str);
		
// 	}
	
// 	free(str);
// 	close(fd);
// }