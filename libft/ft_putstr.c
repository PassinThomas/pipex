/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:44:29 by tpassin           #+#    #+#             */
/*   Updated: 2024/05/16 21:20:25 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(char *s, t_buffer *buff)
{
	int	i;

	i = 0;
	if (!s)
	{
		return (ft_putstr("(null)", buff));
	}
	while (s && s[i])
	{
		ft_putchar(s[i], buff);
		i++;
	}
	if (i < 0)
		return (-1);
	return (i);
}
