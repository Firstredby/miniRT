/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorth <aorth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:49:18 by aorth             #+#    #+#             */
/*   Updated: 2025/11/25 12:13:43 by aorth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

char	*trim_whitespace(char *str)
{
	int		i;
	char	*substr;

	i = ft_strlen(str) - 1;
	while (str[i])
	{
		if (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
			i--;
		else
		{
			i++;
			str[i] = '\0';
			break ;
		}
	}
	i = 0;
	while ((str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	substr = ft_substr(str, i, ft_strlen(str));
	if (!substr)
		return (print_error("Memory allocation failed"), NULL);
	return (substr);
}
