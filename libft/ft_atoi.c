/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:19:27 by tpassin           #+#    #+#             */
/*   Updated: 2024/03/14 01:02:50 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atoi(const char *nptr)
{
	int		i;
	int		sign;
	long	res;
	long	verif;

	i = 0;
	sign = 1;
	res = 0;
	if (ft_strlen(nptr) > 11)
		return (ft_putstr_fd("Error\n", 2), 2147483650);
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
		res = res * 10 + nptr[i++] - '0';
	verif = res * sign;
	if (verif > 2147483647 || verif < -2147483648)
		return (ft_putstr_fd("Error\n", 2), 2147483650);
	return (verif);
}
