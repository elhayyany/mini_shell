/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaouan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 00:19:03 by akaouan           #+#    #+#             */
/*   Updated: 2021/11/15 11:11:40 by akaouan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	size_t	counter;
	size_t	i;

	i = 0;
	counter = size * count;
	p = malloc(counter);
	if (!p)
		return (NULL);
	while (counter > 0)
	{
		((char *)p)[i] = 0;
		i++;
		counter--;
	}
	return (p);
}
