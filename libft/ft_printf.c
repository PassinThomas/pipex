/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 19:57:51 by tpassin           #+#    #+#             */
/*   Updated: 2024/05/18 15:49:38 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_conv(char c, va_list ap, t_buffer *buff)
{
	int	counter;
	int	pt_count;

	pt_count = 0;
	counter = 0;
	if (pt_count < 0)
		return (-1);
	if (c == 's')
		counter += ft_putstr(va_arg(ap, char *), buff);
	else if (c == 'c')
		counter += ft_putchar(va_arg(ap, int), buff);
	else if (c == 'd' || c == 'i')
		counter += ft_putnbr(va_arg(ap, int), &pt_count, buff);
	else if (c == 'u')
		counter += ft_unsigned_nb(va_arg(ap, unsigned int), &pt_count, buff);
	else if (c == 'x' || c == 'X')
		counter += ft_print_hex(va_arg(ap, unsigned int), c, &pt_count, buff);
	else if (c == 'p')
		counter += ft_put_p(va_arg(ap, void *), buff);
	else if (c == '%')
		counter += ft_putchar('%', buff);
	return (counter);
}

int	ft_printf(int fd, const char *str, ...)
{
	va_list		ap;
	int			count;
	int			i;
	t_buffer	buff;

	buff.fd = fd;
	buff.length = 0;
	i = -1;
	count = 0;
	va_start(ap, str);
	if (!str)
		return (-1);
	while (str[++i])
	{
		if (str[i] == '%')
			count += print_conv(str[++i], ap, &buff);
		else
			count += ft_putchar(str[i], &buff);
	}
	va_end(ap);
	if (buff.length)
		count += write(buff.fd, buff.buff, buff.length);
	return (count);
}
// int main()
// {
// 	//int y = ft_printf(0);
// 	ft_printf(1, "salut les gars");
// }
