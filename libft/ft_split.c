/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaouan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 23:59:49 by akaouan           #+#    #+#             */
/*   Updated: 2021/11/16 23:59:53 by akaouan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	calc_strings(const char *s, char c)
{
	int	i;
	int	strings;
	int	sign;

	sign = 0;
	i = 0;
	strings = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i])
		{
			sign++;
			i++;
		}
		if (sign > 0)
			strings++;
		sign = 0;
	}
	return (strings);
}

static	int	chars_counter(const char *s, int i, char c)
{
	int	len;

	len = 0;
	while (s[i] != c && s[i] != '\0')
	{
		len++;
		i++;
	}
	return (len);
}

static	void	*fr_ee(char **strings, int j)
{
	while (j--)
		free(strings[j]);
	free(strings);
	return (NULL);
}

static	char	**ending(const char *s, char c, char **p)
{
	int	i;
	int	k;
	int	j;

	i = 0;
	j = 0;
	while (j < calc_strings(s, c))
	{
		k = 0;
		while (s[i] == c)
			i++;
		p[j] = malloc(sizeof(char) *(chars_counter(s, i, c) + 1));
		if (!p[j])
			return (fr_ee(p, j));
		while (s[i] != c && s[i] != '\0')
		{
			p[j][k++] = s[i];
			i++;
		}
		p[j++][k] = '\0';
	}
	p[j] = 0;
	return (p);
}

char	**ft_split(char const *s, char c)
{
	char	**p;

	if (!s)
		return (NULL);
	p = malloc(sizeof(char *) * (calc_strings(s, c) + 1));
	if (!p)
		return (NULL);
	return (ending(s, c, p));
}
