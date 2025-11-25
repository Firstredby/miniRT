/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorth <aorth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:44:52 by aorth             #+#    #+#             */
/*   Updated: 2025/11/12 11:58:50 by aorth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			ts;
	void			*mem;
	unsigned char	*ptr;
	size_t			i;

	if (size > 0 && (nmemb > SIZE_MAX / size))
		return (NULL);
	ts = nmemb * size;
	mem = malloc(ts);
	if (!mem)
		return (NULL);
	ptr = (unsigned char *)mem;
	i = 0;
	while (i < ts)
		ptr[i++] = 0;
	return (mem);
}

size_t	ft_strlen_size(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_strchr_int(const char *s, int c)
{
	int	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i + 1);
		i++;
	}
	if (c == '\0')
		return (i);
	return (-1);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	t_len;
	char	*s3;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	t_len = (ft_strlen_size(s1) + ft_strlen_size(s2));
	s3 = ft_calloc((t_len + 1), sizeof(char));
	if (!s3)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i] != '\0')
	{
		s3[i++] = s1[j++];
	}
	i = 0;
	while (s2 && s2[i] != '\0')
	{
		s3[j++] = s2[i++];
	}
	return (s3);
}

void	ft_free(char **ptr)
{
	if (ptr != NULL && *ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}
