/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_line_check_vii.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 17:36:56 by ael-hayy          #+#    #+#             */
/*   Updated: 2022/08/01 09:13:36 by ael-hayy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/minishell.h"

int	check_andor_i(char *line, int *k, int *i)
{
	if (line[(*i) + 1] == '|' || line[(*i) + 1] == '&')
		(*i)++;
	(*k) = (*i) + 1;
	while ((*k) >= 0)
	{
		while (line[(*k)] == ' ')
			(*k)++;
		if (line[(*k)] == '|' || line[(*k)] == '&' \
		|| line[(*i)] == '(' || line[(*i)] == ')')
		{
			check_dir_ii(line[(*k)]);
			return (1);
		}
		else
			break ;
	}
	if ((*k) == 0 && line[(*k)] == ' ')
	{
		check_dir_ii(line[(*k)]);
		return (1);
	}
	return (0);
}

int	check_andor_ii(char *line, int *k, int *i, int *j)
{
	while (line[(*i)] == ' ')
		(*i)++;
	if (!line[(*i)])
		return (1);
	(*j) = 0;
	if (line[(*i)] == '&' && line[(*i) + 1] != '&')
	{
		check_dir_ii(line[(*k)]);
		return (1);
	}
	if ((*i) == 0)
		return (1);
	else
	{
		if (check_andor_i(line, k, i))
			return (1);
	}
	return (0);
}

int	check_andor_iii(char *line, int *i, int *k, int *j)
{
	while (line[(*i)] == ' ')
		(*i)++;
	if (!j && (line[(*i)] == '|' || line[(*i)] == '&'))
	{
		check_dir_ii(line[(*k)]);
		return (1);
	}
	(*j) = 1;
	if (line[(*i)] == '\"' || line[(*i)] == '\'')
		(*i) += next_qoute(&line[(*i)], line[(*i)]);
	return (0);
}

int	check_andor_vi(char *line, int *i, int *l)
{
	static int	j;
	static int	k;

	if (check_andor_iii(line, i, &k, &j))
		return (1);
	if (line[(*i)] == '|' || line[(*i)] == '&')
	{	
		if ((*l) == 0)
			return (1);
		if (check_andor_ii(line, &k, &(*i), &j))
			return (1);
		(*l) = 0;
	}
	if (line[(*i)] != ' ' && !(line[(*i)] == '|' || line[(*i)] == '&'))
		(*l) = 1;
	if (line[(*i)] != '|' && line[(*i)] != '&')
		j = 1;
	return (0);
}

int	check_andor(char *line)
{
	int	i;
	int	l;
	int	len;

	len = ft_strlen(line);
	i = 0;
	l = 0;
	while (i < len)
	{
		if (check_andor_vi(line, &i, &l))
			return (1);
		i++;
	}
	if (l == 0)
		return (1);
	return (0);
}
