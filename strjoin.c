/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 15:56:44 by ael-hayy          #+#    #+#             */
/*   Updated: 2022/08/05 11:46:36 by ael-hayy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/minishell.h"

char	*ft_strjoinn(char *s1, char const *s2)
{
	int		i;
	char	*p;
	int		len;
	int		j;

	if (s1 == NULL || s2 == NULL)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	p = malloc(sizeof(char) * len);
	i = 0;
	j = 0;
	if (!p)
		return (NULL);
	while (s1[j])
		p[i++] = s1[j++];
	j = 0;
	while (s2[j])
		p[i++] = s2[j++];
	p[i] = '\0';
	if (s1)
		free(s1);
	s1 = 0;
	return (p);
}
