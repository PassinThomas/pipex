/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:43:20 by tpassin           #+#    #+#             */
/*   Updated: 2024/05/18 15:32:30 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(int c, t_buffer *buff)
{
	if (buff->length == 1024)
	{
		buff->length = 0;
		return (write(buff->fd, buff->buff, 1024));
	}
	buff->buff[buff->length++] = c;
	return (0);
}
