/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_shell_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 13:33:33 by ael-hayy          #+#    #+#             */
/*   Updated: 2022/08/01 08:48:01 by ael-hayy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/minishell.h"

char	*clear_it(char *slice)
{
	char	*line;
	int		i;
	int		k;

	i = 0;
	k = ft_strlen(slice) - 1;
	line = slice;
	while (slice[i] && slice[i] == ' ')
		i++;
	if (slice[i] == '(')
		i++;
	while (slice[i] && slice[i] == ' ')
		i++;
	while (k >= 0 && slice[k] == ' ')
		k--;
	if (slice[k] == ')')
		k--;
	while (line[k] == ' ')
		k--;
	line = new_slice(slice, i, k);
	free (slice);
	return (line);
}

void	m_shell(char **slices, t_prior *script)
{
	int	i;

	i = 0;
	while (slices[i])
	{
		slices[i] = clear_it(slices[i]);
		i++;
	}
	i = 0;
	while (slices[i])
	{
		script->next[i] = m_shell_parser(slices[i]);
		i++;
	}
}

t_prior	*m_shell_parser(char *line)
{
	char	**slices;
	t_prior	*script;

	script = 0;
	script = malloc(sizeof(t_prior));
	check_malloc(script, 0, 1);
	script->operator = 0;
	if (calulate_cmds(line) > 1)
		script->operator = malloc(sizeof(char *) * (calulate_cmds(line) + 1));
	slices = ft_split_pro(line, script->operator);
	script->numofchilds = strsnums(slices);
	script->line = line;
	script->slices = slices;
	if (strsnums(slices) == 1)
	{
		script->numofchilds = 0;
		return (script);
	}
	script->next = malloc(sizeof(t_prior *) * strsnums(slices));
	m_shell(slices, script);
	g_global.con = script->numofchilds;
	return (script);
}
