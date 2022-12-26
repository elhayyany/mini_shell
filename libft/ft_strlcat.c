/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaouan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:19:04 by akaouan           #+#    #+#             */
/*   Updated: 2021/11/17 17:19:09 by akaouan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;
	size_t	j;

	dest_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	j = ft_strlen(dst);
	i = 0;
	if (dstsize == 0 || dstsize <= dest_len)
		return (dstsize + src_len);
	else
	{
		while (src[i] && j < dstsize - 1)
		{
			dst[j] = src[i];
			i++;
			j++;
		}
		dst[j] = '\0';
		return (dest_len + src_len);
	}
}
