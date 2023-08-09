/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdjan <bdjan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 11:42:03 by bdjan             #+#    #+#             */
/*   Updated: 2023/07/14 12:08:00 by bdjan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_rd_str(int fd, char *input_str)
{
	char	*buffer;
	char	*temp;
	int		rd_bytes;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	rd_bytes = 1;
	while (!ft_strchr(input_str, '\n') && rd_bytes != 0)
	{
		rd_bytes = read(fd, buffer, BUFFER_SIZE);
		if (rd_bytes == -1)
			return (free(buffer), free(input_str), NULL);
		buffer[rd_bytes] = '\0';
		temp = ft_strjoin(input_str, buffer);
		free(input_str);
		input_str = temp;
	}
	return (free(buffer), input_str);
}

char	*ft_extract_line(char *input_str, int i)
{
	char	*str;

	if (!input_str[i])
		return (NULL);
	while (input_str[i] && input_str[i] != '\n')
		i++;
	if (input_str[i] == '\n')
		i++;
	str = malloc(i + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (input_str[i] && input_str[i] != '\n')
	{
		str[i] = input_str[i];
		i++;
	}
	if (input_str[i] == '\n')
	{
		str[i] = input_str[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_new_str(char *input_str)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (input_str[i] && input_str[i] != '\n')
		i++;
	if (!input_str[i])
		return (free(input_str), NULL);
	str = malloc((ft_strlen(input_str) - i + 1) * sizeof(char));
	if (!str)
		return (free(input_str), NULL);
	i++;
	j = 0;
	while (input_str[i])
		str[j++] = input_str[i++];
	str[j] = '\0';
	return (free(input_str), str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*input_str[1024]; 
	int			i;

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (!input_str[fd])
		input_str[fd] = ft_strdup("");
	input_str[fd] = ft_rd_str(fd, input_str[fd]);
	if (!input_str[fd])
		return (NULL);
	line = ft_extract_line(input_str[fd], i);
	input_str[fd] = ft_new_str(input_str[fd]);
	return (line);
}
