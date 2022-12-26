/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaouan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:50:56 by akaouan           #+#    #+#             */
/*   Updated: 2021/11/17 16:51:13 by akaouan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	int	i;
	int	lst_len;

	lst_len = ft_lstsize(lst) - 1;
	i = 0;
	if (lst == NULL)
		return (lst);
	else
	{
		while (i < lst_len)
		{
			lst = lst->next;
			i++;
		}
	}
	return (lst);
}
