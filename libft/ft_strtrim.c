/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaouan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 00:55:50 by akaouan           #+#    #+#             */
/*   Updated: 2021/11/15 11:41:51 by akaouan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*concat(int start, int end, char *p, const	char *s1)
{
	int	j;

	j = 0;
	while (start <= end)
		p[j++] = s1[start++];
	p[j] = '\0';
	return (p);
}

static	int	check(const char *s1, const char set)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] == set)
			return (1);
		i++;
	}
	return (0);
}

static	int	get_end(const char *s1, const char *set)
{
	int	end;

	end = ft_strlen(s1) - 1;
	while (check(set, s1[end]))
		end--;
	return (end);
}

char	*ft_strtrim(const char *s1, char const *set)
{
	int		start;
	int		end;
	char	*p;

	end = 0;
	start = 0;
	if (s1 == NULL)
		return (NULL);
	while (check(set, s1[start]))
		start++;
	if (start == (int)ft_strlen(s1))
	{
		p = malloc(sizeof(char) * 1);
		p[0] = '\0';
		return (p);
	}
	else
	{
		end = get_end(s1, set);
		p = malloc(sizeof(char) * (end - start) + 2);
		if (!p)
			return (NULL);
		concat(start, end, p, s1);
		return (p);
	}
}
