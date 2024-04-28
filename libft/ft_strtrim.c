/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:21:00 by tpassin           #+#    #+#             */
/*   Updated: 2023/11/22 16:12:29 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_sep(char const c, char const *sep)
{
	int	i;

	i = 0;
	while (sep[i])
	{
		if (sep[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	start_skip(char const *str, char const *sep)
{
	int	i;

	i = 0;
	while (str[i] && check_sep(str[i], sep))
	{
		i++;
	}
	return (i);
}

int	end_skip(char const *s, char const *sep)
{
	unsigned int	max;
	unsigned int	count;

	max = ft_strlen(s);
	count = 0;
	if (max > 0)
	{
		while (max > 0 && check_sep(s[max - 1], sep) && max)
		{
			max--;
			count++;
		}
	}
	return (count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*str;
	unsigned int	min;
	unsigned int	max;
	unsigned int	trimmed_len;

	if (!s1 || !set)
		return (NULL);
	min = start_skip(s1, set);
	max = end_skip(s1, set);
	if (min == ft_strlen(s1) || max == ft_strlen(s1))
		return (ft_strdup(""));
	trimmed_len = (ft_strlen(s1) - (min + max));
	str = (char *)malloc(sizeof(char) * (trimmed_len + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1 + min, trimmed_len + 1);
	return (str);
}
