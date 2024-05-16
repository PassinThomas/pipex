/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 20:33:50 by tpassin           #+#    #+#             */
/*   Updated: 2024/05/16 21:18:55 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_print_hex(unsigned int nb, char c, int *ptr, t_buffer *buff)
{
	char	*base;

	if (c == 'x')
		base = "0123456789abcdef";
	else if (c == 'X')
		base = "0123456789ABCDEF";
	if (nb < 16)
		*ptr += ft_putchar(base[nb], buff);
	else
	{
		ft_print_hex(nb / 16, c, ptr, buff);
		*ptr += ft_putchar(base[nb % 16], buff);
	}
	return (*ptr);
}
