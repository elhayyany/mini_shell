/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaouan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 01:32:34 by akaouan           #+#    #+#             */
/*   Updated: 2021/11/14 21:20:39 by akaouan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static	char	*concat(char *p, long save_n, int last_num, int sign)
{
	p[last_num--] = '\0';
	while (save_n > 0)
	{
		p[last_num--] = (save_n % 10) + '0';
		save_n /= 10;
	}
	if (sign > 0)
		p[last_num] = '-';
	return (p);
}

static	int	num_size(long n)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static	char	*alloc_zero(char *p)
{
	p = malloc(sizeof(char) * 2);
	if (!p)
		return (NULL);
	p[0] = '0';
	p[1] = '\0';
	return (p);
}

char	*ft_itoa(int n)
{
	int		size;
	int		sign;
	char	*p;
	long	save_n;
	long	num;

	p = NULL;
	if (n == 0)
		return (alloc_zero(p));
	num = n;
	sign = 0;
	size = 0;
	if (num < 0)
	{
		sign++;
		num *= -1;
	}
	save_n = num;
	size = num_size(num);
	p = malloc(sizeof(char) * size + 1 + sign);
	if (!p)
		return (NULL);
	concat(p, save_n, sign + size, sign);
	return (p);
}
