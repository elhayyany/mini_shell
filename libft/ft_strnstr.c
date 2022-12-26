/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaouan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 22:14:30 by akaouan           #+#    #+#             */
/*   Updated: 2021/11/15 11:20:33 by akaouan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strnstr(const char *s, const char *chr, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (*chr == '\0')
		return ((char *)s);
	while (s[i] && i < len)
	{
		if (s[i] == chr[j])
		{
			while (s[i + j] == chr[j] && i + j < len && chr[j])
				j++;
			if (!chr[j])
				return ((char *)s + i);
			else
				j = 0;
		}
		i++;
	}
	return (NULL);
}
