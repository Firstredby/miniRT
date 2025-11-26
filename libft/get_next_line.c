/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:44:56 by aorth             #+#    #+#             */
/*   Updated: 2025/11/26 10:38:51 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_extract_next_line(char *buffer, char *line)
{
	int		i;
	int		j;
	char	*next_line;

	if (!buffer)
		return (NULL);
	if (ft_strchr_int(buffer, '\0') != -1 && ft_strchr_int(buffer, '\n') == -1)
		return (ft_free(&buffer), NULL);
	else
		i = ft_strlen_size(line);
	next_line = ft_calloc((ft_strlen_size(buffer) - i + 1), sizeof(char));
	if (!next_line)
		return (ft_free(&buffer), NULL);
	j = 0;
	while (buffer[i])
		next_line[j++] = buffer[i++];
	ft_free(&buffer);
	return (next_line);
}

char	*ft_extract_end(char *buffer)
{
	int		i;
	int		end;
	char	*next_line;

	if (!buffer || !buffer[0])
		return (NULL);
	end = ft_strchr_int(buffer, '\0');
	if (end != -1)
	{
		next_line = ft_calloc(end + 1, sizeof(char));
		if (!next_line)
			return (NULL);
		i = 0;
		while (end--)
		{
			next_line[i] = buffer[i];
			i++;
		}
		return (next_line);
	}
	return (NULL);
}

char	*ft_extract_line(char *buffer)
{
	int		i;
	int		nl;
	char	*next_line;

	if (!buffer || !buffer[0])
		return (NULL);
	nl = ft_strchr_int(buffer, '\n');
	if (nl != -1)
	{
		next_line = ft_calloc(nl + 1, sizeof(char));
		if (!next_line)
			return (NULL);
		i = 0;
		while (nl--)
		{
			next_line[i] = buffer[i];
			i++;
		}
		return (next_line);
	}
	else
		return (ft_extract_end(buffer));
}

char	*ft_read_file(char *buffer, int fd)
{
	char	*temp_buffer;
	char	*temp;
	int		bytes;

	bytes = 1;
	while (bytes > 0)
	{
		temp_buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!temp_buffer)
			return (ft_free(&buffer), NULL);
		bytes = read(fd, temp_buffer, BUFFER_SIZE);
		if (bytes == -1)
			return (ft_free(&temp_buffer), ft_free(&buffer), NULL);
		if (bytes == 0)
			return (ft_free(&temp_buffer), buffer);
		temp = buffer;
		buffer = ft_strjoin(temp, temp_buffer);
		if (!buffer)
			return (ft_free(&temp_buffer), ft_free(&temp), NULL);
		ft_free(&temp);
		ft_free(&temp_buffer);
		if (ft_strchr_int(buffer, '\n') != -1)
			break ;
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*main_buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (main_buffer)
			ft_free(&main_buffer);
		return (NULL);
	}
	if (ft_strchr_int(main_buffer, '\n') == -1)
		main_buffer = ft_read_file(main_buffer, fd);
	if (!main_buffer)
		return (NULL);
	line = ft_extract_line(main_buffer);
	if (!line)
		ft_free(&main_buffer);
	else
	{
		main_buffer = ft_extract_next_line(main_buffer, line);
		if (!main_buffer)
			ft_free(&main_buffer);
	}
	return (line);
}
