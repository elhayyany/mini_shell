/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 00:14:08 by akaouan           #+#    #+#             */
/*   Updated: 2022/08/05 13:13:11 by ael-hayy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	is_alpha(int c)
{
	if (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) && c != '_')
		return (0);
	return (1);
}

static	int	is_num(int c)
{
	if (c >= '0' && c <= '9')
		return (0);
	return (1);
}

int	ft_isalnum(int c)
{
	if (is_alpha(c) && is_num(c) && c != '?')
		return (0);
	return (1);
}
