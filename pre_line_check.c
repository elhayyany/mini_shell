/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_line_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 09:50:03 by ael-hayy          #+#    #+#             */
/*   Updated: 2022/08/01 09:24:01 by ael-hayy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/minishell.h"

int	rev_next_quote(char *line, int j, char c)
{
	j--;
	while (j >= 0 && line[j] != c)
		j--;
	return (j);
}

int	revcheck_i(char *line, int k, int i)
{
	while (k < (int)ft_strlen(line))
	{
		if (line[k] == ' ')
		{
			k++;
			continue ;
		}
		if (line[k] == '|' || line[k] == '&' || line[i] == ')')
		{
			check_dir_ii(line[i]);
			return (1);
		}
		else
			break ;
	}
	if (k == (int)ft_strlen(line) - 1 && line[k] == ' ')
	{
		check_dir_ii(line[i]);
		return (1);
	}
	return (0);
}

int	revcheck(char *line)
{
	int	i;
	int	k;

	i = ft_strlen(line);
	while (--i >= 0)
	{
		if (line[i] == '\"' || line[i] == '\'')
			i = rev_next_quote(line, i, line[i]);
		while (i >= 0 && line[i] == ' ')
			i--;
		if (i >= 0 && (line[i] == '|' || line[i] == '&'))
		{
			if (i == (int)ft_strlen(line) - 1)
				return (1);
			else
			{
				k = i + 1;
				if (revcheck_i(line, k, i))
					return (1);
			}
			if (line[i - 1] == '|' || line[i - 1] == '&')
				i--;
		}
	}
	return (0);
}

int	pre_check_line(char *line)
{
	g_global.is_printed = 0;
	if (check_parentheses(line) || check_andor(line) \
	|| revcheck(line) || check_dir(line))
	{
		if (g_global.is_printed == 0)
			write(2, ">$ syntax error unexpected token \n", 34);
		return (1);
	}
	return (0);
}
