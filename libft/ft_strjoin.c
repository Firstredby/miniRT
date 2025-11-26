/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorth <aorth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:28:15 by ishchyro          #+#    #+#             */
/*   Updated: 2025/11/26 15:06:33 by aorth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	t_len;
	char	*s3;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	t_len = (ft_strlen(s1) + ft_strlen(s2));
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
