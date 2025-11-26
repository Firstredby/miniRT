/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:04:24 by ishchyro          #+#    #+#             */
/*   Updated: 2025/11/26 10:35:08 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_valid_help(long temp)
{
	if (temp < -2147483648 || temp > 2147483647)
		return (0);
	return (1);
}

static int	atol_helper(const char *str, int n)
{
	int	i;

	i = n;
	while (str[i] == '0')
		i++;
	if (ft_strlen(str) - i > 10)
		return (0);
	return (1);
}

long	ft_atol(const char *nptr)
{
	long	result;
	int		sign;
	int		i;

	i = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	sign = 1;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i++] == '-')
			sign *= -1;
	}
	if (!ft_isdigit(nptr[i]))
		print_error("Agrument is not a number");
	if (!atol_helper(nptr, i))
		print_error("Argument is too long");
	result = 0;
	while (nptr[i] && ft_isdigit(nptr[i]))
		result = result * 10 + nptr[i++] - '0';
	if (nptr[i] && !ft_isdigit(nptr[i]))
		return (0);
	if (!is_valid_help(result))
		print_error("Argument is too long");
	return (result * sign);
}
