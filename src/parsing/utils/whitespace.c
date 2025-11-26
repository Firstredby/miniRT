/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whitespace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorth <aorth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 13:19:26 by aorth             #+#    #+#             */
/*   Updated: 2025/11/26 17:53:01 by aorth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/parsing.h"

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

int	is_whitespace(char c)
{
	if ((c == 32 || (c >= 9 && c <= 13)))
		return (1);
	return (0);
}
