/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_nb.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 18:49:38 by tpassin           #+#    #+#             */
/*   Updated: 2024/05/16 21:20:33 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_unsigned_nb(unsigned int nb, int *ptr, t_buffer *buff)
{
	if (nb > 9)
		ft_unsigned_nb(nb / 10, ptr, buff);
	*ptr += ft_putchar(nb % 10 + 48, buff);
	return (*ptr);
}
