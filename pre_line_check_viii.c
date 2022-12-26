/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_line_check_viii.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 17:38:59 by ael-hayy          #+#    #+#             */
/*   Updated: 2022/08/01 09:22:45 by ael-hayy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/minishell.h"

int	check_dir_ii(char c)
{
	g_global.is_printed = 1;
	write(2, ">$ syntax error near unexpected token `", 40);
	write(2, &c, 1);
	write(2, "'\n", 2);
	return (1);
}

int	check_dir_i(int i, char *line, char c, char g)
{
	while (line[i] == ' ')
		i++;
	if (!line[i])
	{
		g_global.is_printed = 1;
		write(2, ">$ syntax error near unexpected token `>'\n", 42);
		return (1);
	}
	while (line[i] == ' ')
		i++;
	if (line[i] == g || line[i] == '|' || line[i] == '&' \
	|| line[i] == '(' || line[i] == ')')
		return (check_dir_ii(line[i]));
	if (line[i] == c)
	{
		i++;
		while (line[i] == ' ')
			i++;
		if (line[i] == '<' || line[i] == '>' || line[i] == '|' \
		|| line[i] == '&' || line[i] == '(' || line[i] == ')')
			return (check_dir_ii(line[i]));
	}
	return (0);
}

int	check_o(char *line, int *i, char c, char g)
{
	while (line[(*i)] == ' ')
		(*i)++;
	if (check_dir_i((*i), line, c, g))
		return (1);
	return (0);
}

int	check_dir(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '<')
		{
			i++;
			if (line[i] == '<')
				if (!line[i + 1])
					return (1);
			if (check_o(line, &i, '<', '>'))
				return (1);
		}
		else if (line[i] == '>')
		{
			i++;
			if (check_o(line, &i, '>', '<'))
				return (1);
		}
		i++;
	}
	return (0);
}
