/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpassin <tpassin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 20:06:39 by tpassin           #+#    #+#             */
/*   Updated: 2024/02/23 07:48:39 by tpassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(char const *str, char sep)
{
	int	i;
	int	etat;
	int	count;

	i = 0;
	etat = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == sep && str[i])
			etat = 0;
		else if (etat == 0)
		{
			etat = 1;
			count++;
		}
		i++;
	}
	return (count);
}

static char	*ft_strndup(char const *s, int i, int j)
{
	int		k;
	char	*dest;

	k = 0;
	dest = (char *)malloc(sizeof(char) * ((j - i) + 1));
	if (!dest)
		return ((NULL));
	while (i < j)
	{
		dest[k] = s[i];
		i++;
		k++;
	}
	dest[k] = '\0';
	return (dest);
}

static char	**ft_free_split(char **s, int i)
{
	while (i > 0)
	{
		i--;
		free(s[i]);
	}
	free(s);
	return (NULL);
}

static char	**split_logic(char const *s, char c, char **strs)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		j = i;
		if (s[j] != c && s[j])
		{
			while (s[j] != c && s[j])
				j++;
			strs[k] = ft_strndup(s, i, j);
			if (!strs[k])
				return (ft_free_split(strs, k));
			k++;
			i = j;
		}
	}
	strs[k] = (NULL);
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;

	if (!s)
		return (NULL);
	strs = (char **)malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (!strs)
		return (NULL);
	return (split_logic(s, c, strs));
}
