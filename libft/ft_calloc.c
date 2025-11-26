/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorth <aorth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:43:13 by ishchyro          #+#    #+#             */
/*   Updated: 2025/11/26 15:07:51 by aorth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
