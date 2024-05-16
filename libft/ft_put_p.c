/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:25:16 by tpassin           #+#    #+#             */
/*   Updated: 2024/05/16 21:19:35 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_base16(unsigned long nb, char *base, t_buffer *buff)
{
	int	count;

	count = 0;
	if (nb < 16)
		count += ft_putchar(base[nb], buff);
	else
	{
		count += ft_base16(nb / 16, base, buff);
		count += ft_base16(nb % 16, base, buff);
	}
	if (count < 0)
		return (-1);
	return (count);
}

int	ft_put_p(void *nbr, t_buffer *buff)
{
	int				count;
	char			*base;
	unsigned long	nb;

	count = 0;
	if (nbr == 0)
		return (count += ft_putstr("(nil)", buff));
	nb = (unsigned long)nbr;
	base = "0123456789abcdef";
	count += ft_putstr("0x", buff);
	count += ft_base16(nb, base, buff);
	if (count < 0)
		return (-1);
	return (count);
}
