/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaouan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 00:27:04 by akaouan           #+#    #+#             */
/*   Updated: 2021/11/17 18:18:14 by akaouan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*alloc_back(char *s)
{	
	s = malloc(sizeof(char) * 1);
	s[0] = '\0';
	return (s);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	size;
	size_t	i;
	char	*p;

	size = 0;
	i = 0;
	p = NULL;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		p = alloc_back(p);
		return (p);
	}
	while (size < len && s[size])
		size++;
	p = malloc(sizeof(char) * size + 1);
	if (!p)
		return (NULL);
	while (i < size)
		p[i++] = s[start++];
	p[i] = '\0';
	return (p);
}
