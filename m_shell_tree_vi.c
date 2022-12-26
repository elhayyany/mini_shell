/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_shell_tree_vi.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 17:41:41 by ael-hayy          #+#    #+#             */
/*   Updated: 2022/08/05 19:49:54 by ael-hayy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/minishell.h"

void	check_malloc(void *p, void **ptr, int i)
{
	if (i)
	{
		if (!p)
		{
			ft_putendl_fd("can't allocate more space", STDERR_FILENO);
			exit(1);
		}
		return ;
	}
	if (!ptr)
	{
		ft_putendl_fd("can't allocate more space", STDERR_FILENO);
		exit(1);
	}
}

int	strsnums(char **slices)
{
	int	i;

	if (!slices)
		return (0);
	i = 0;
	while (slices[i])
		i++;
	return (i);
}

int	closed_parentheses(char *line)
{
	int	i;
	int	j;

	i = 1;
	j = 1;
	while (line[i])
	{
		if (line[i] == '(')
			j++;
		if (line[i] == ')')
			j--;
		if (j == 0)
			return (i);
		i++;
	}
	return (i);
}

int	calulate_cmds(char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '|' || line[i] == '&')
		{
			if (line[i + 1] == '|' || line [i + 1] == '&')
				i++;
			j++;
		}
		if (line[i] == '(')
			i += closed_parentheses(&line[i]);
		if (line[i] == '\'' || line[i] == '"' )
			i += next_qoute(&line[i], line[i]);
		i++;
	}
	j++;
	return (j);
}

void	calulate_cmds_lens_o(char *line, int *i, int *k)
{
	if (line[(*i)] == '(')
	{
		(*k) += closed_parentheses(&line[(*i)]);
		(*i) += closed_parentheses(&line[(*i)]);
	}
	else if (line[(*i)] == '\'' || line[(*i)] == '"')
	{
		(*k) += next_qoute(&line[(*i)], line[(*i)]);
		(*i) += next_qoute(&line[(*i)], line[(*i)]);
	}
}
