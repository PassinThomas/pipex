/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:48:50 by tpassin           #+#    #+#             */
/*   Updated: 2024/05/16 21:20:08 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(int n, int *ptr, t_buffer *buff)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		*ptr += ft_putchar('-', buff);
		nb *= -1;
	}
	if (nb > 9)
		ft_putnbr(nb / 10, ptr, buff);
	*ptr += ft_putchar(nb % 10 + 48, buff);
	return (*ptr);
}
