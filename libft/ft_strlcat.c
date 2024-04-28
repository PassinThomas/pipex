/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:20:41 by tpassin           #+#    #+#             */
/*   Updated: 2023/11/17 17:04:20 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	j = 0;
	if (size == 0)
		return (ft_strlen(src));
	if (size <= ft_strlen(dst) || size == 0)
		return (ft_strlen(src) + size);
	i = ft_strlen(dst);
	while (i < size - 1 && src[j])
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (ft_strlen(&src[j]) + ft_strlen(dst));
}

/*int main(int ac, char **av)
{
	if (ac == 4)
	{
		printf("%li\n", strlcat(av[1], av[2], atoi(av[3])));
        	printf("%li\n", ft_strlcat(av[1], av[2], atoi(av[3])));
	}		
}*/
