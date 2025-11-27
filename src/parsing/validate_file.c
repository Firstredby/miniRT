/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorth <aorth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:30:10 by aorth             #+#    #+#             */
/*   Updated: 2025/11/27 10:23:46 by aorth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

static int	validate_end(char *filename, char *end)
{
	int	i;
	int	j;

	i = ft_strlen(filename) - 1;
	j = 2;
	while (filename[i] && end[j] && filename[i] == end[j])
	{
		j--;
		i--;
		if (j == -1)
			break ;
	}
	if (j != -1)
		return (0);
	if (filename[i] && filename[i] == '/')
		return (0);
	return (1);
}

int	validate_file(char *filename)
{
	if (!filename)
		return (print_error("File does not exist"), 0);
	if (!validate_end(filename, ".rt"))
		return (print_error("Invalid file extension. Expected .rt"), 0);
	return (1);
}
