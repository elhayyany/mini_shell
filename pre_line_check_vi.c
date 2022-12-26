/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_line_check_vi.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 17:35:37 by ael-hayy          #+#    #+#             */
/*   Updated: 2022/08/07 15:31:15 by ael-hayy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/minishell.h"

int	all_space(char *line)
{
	int	i;

	i = 0;
	if (line[0] == '"')
	{
		if (line[1] == '"')
		{
			if (line[2] == '\0')
			{
				printf("minishell(v4.6): : command not found\n");
				g_global.exit_status = 1;
				return (0);
			}
		}
	}
	while (line[i])
	{
		if (line[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int	next_qoute(char *line, char c)
{
	int	i;

	i = 1;
	while (line[i])
	{
		if (line[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	check_parentheses_ii(char *line, int *i, int *j, int *k)
{
	if (line[(*i)] == '\"' || line[(*i)] == '\'')
	{
		if (next_qoute(&line[(*i)], line[(*i)]) == -1)
		{
			g_global.is_printed = 1;
			write(2, ">$ syntax error Unclosed qoute\n", 31);
			return (1);
		}
		(*i) += next_qoute(&line[(*i)], line[(*i)]);
	}
	else if (line[(*i)] == '(')
	{
		if (check_parentheses_i(line, i, j, k))
			return (1);
	}
	else if (line[(*i)] == ')')
		(*j)--;
	if ((*j) < 0)
		return (1);
	return (0);
}

int	check_parentheses_i(char *line, int *i, int *j, int *k)
{
	if ((*i) == 0)
		(*j)++;
	else
	{
		(*k) = (*i) - 1;
		while ((*k) >= 0)
		{
			if (line[(*k)] == ' ')
			{
				(*k)--;
				continue ;
			}
			if (line[(*k)] != '|' && line[(*k)] != '&' && line[(*k)] != '(')
			{
				check_dir_ii(line[*k]);
				return (1);
			}
			else
				break ;
			(*k)--;
		}
		(*j)++;
	}
	return (0);
}

int	check_parentheses(char *line)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (line[i] == ' ')
		i++;
	while (line[i])
	{
		if (check_parentheses_ii(line, &i, &j, &k))
			return (1);
		i++;
	}
	if (j != 0)
	{
		g_global.is_printed = 1;
		write(2, ">$ syntax error near unexpected token `('\n", 42);
		return (1);
	}
	return (0);
}
