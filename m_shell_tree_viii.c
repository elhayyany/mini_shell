/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_shell_tree_viii.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 17:41:49 by ael-hayy          #+#    #+#             */
/*   Updated: 2022/07/31 20:43:20 by ael-hayy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/minishell.h"

void	get_substr_oi(char *line, int i, int start, char **operator)
{
	int	j;

	j = 0;
	while (line[i] == ' ' || line[i] == ')' || line[i] == '(')
		i++;
	while (line[i] == '|' || line[i] == '&')
	{
		operator[start][j] = line[i];
		j++;
		i++;
	}
	operator[start][j] = '\0';
}

char	*get_substr(char *line, int *len, int start, char **operator)
{
	char	*slice;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	if (start == 0)
		return (get_substr_i(line, len, start, operator));
	slice = malloc(sizeof(char) * len[start] + 1);
	i = lenplusstar(len, start);
	while (line[i] == ' ' || line[i] == '|' || line[i] == '&')
	{
		k++;
		i++;
	}
	j = 0;
	while (j < len[start] - k)
		slice[j++] = line[i++];
	slice[j] = '\0';
	get_substr_oi(line, i, start, operator);
	return (slice);
}

void	get_operators(char ***operators, char *line, int *lens, int i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (j <= i)
	{
		k += lens[j];
		j++;
	}
	j = 0;
	while (line[k] && (line[k] != '|' && line[k] != '&'))
		k++;
	while (line[k] && (line[k] == '|' || line[k] == '&'))
	{
		(*operators)[i][j] = line[k];
		j++;
		k++;
	}
}

char	**ft_split_pro(char *line, char **operators)
{
	char	**slices;
	int		num_of_cmds;
	int		*lens;
	int		i;

	num_of_cmds = calulate_cmds(line);
	lens = malloc(sizeof(int) * (num_of_cmds));
	calulate_cmds_lens(line, lens);
	slices = allocate(lens, num_of_cmds);
	i = 0;
	while (i < num_of_cmds)
	{
		if (operators)
			operators[i] = malloc(sizeof(char) * 3);
		slices[i] = get_substr(line, lens, i, operators);
		i++;
	}
	if (num_of_cmds > 1)
		operators[i] = NULL;
	slices[i] = NULL;
	free(lens);
	return (slices);
}

char	*new_slice(char *slice, int i, int j)
{
	int		k;
	char	*line;

	k = 0;
	line = malloc(sizeof(char *) * (j - i + 1));
	while (i <= j)
	{
		line[k] = slice[i];
		k++;
		i++;
	}
	line[k] = '\0';
	return (line);
}
