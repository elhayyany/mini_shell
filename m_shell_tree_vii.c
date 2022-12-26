/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_shell_tree_vii.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 17:41:45 by ael-hayy          #+#    #+#             */
/*   Updated: 2022/07/31 19:56:56 by ael-hayy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/minishell.h"

void	calulate_cmds_lens(char *line, int *arr)
{
	int	i;
	int	j;
	int	l;
	int	k;

	i = 0;
	j = 0;
	l = 0;
	k = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"' || line[i] == '(')
			calulate_cmds_lens_o(line, &i, &k);
		else if (line[i] == '|' || line[i] == '&')
		{
			arr[l++] = k - j;
			j = k;
			i++;
			if (line[i + 1] == '|' || line [i + 1] == '&')
				i++;
		}
		i++;
		k++;
	}
	arr[l] = k - j;
}

char	**allocate(int *lens, int i)
{
	char	**slices;

	slices = malloc(sizeof(char *) * (i + 1));
	check_malloc(0, (void **)slices, 0);
	(void)lens;
	slices[i] = NULL;
	return (slices);
}

int	lenplusstar(int *len, int start)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < start)
	{
		j += len[i];
		j++;
		i++;
	}
	return (j);
}

char	*clean_slice(char *slice)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = ft_strlen(slice) - 1;
	while (slice[i] && (slice[i] == ' ' || slice[i] == '|' || slice[i] == '&'))
		i++;
	while (j >= 0 && (slice[j] == ' ' || slice[j] == '|' || slice[j] == '&'))
		j--;
	line = malloc(sizeof(char) * (j - i + 1));
	while (i < j)
	{
		line[i] = slice[i];
		i++;
	}
	line[i] = '\0';
	free(slice);
	return (line);
}

char	*get_substr_i(char *line, int *len, int start, char **operator)
{
	int		i;
	int		j;
	char	*slice;

	slice = malloc(sizeof(char) * len[start] + 1);
	check_malloc(slice, 0, 1);
	i = 0;
	j = 0;
	while (i < len[start])
	{
		slice[i] = line[i];
		i++;
	}
	slice[i] = '\0';
	while (line[i] == ' ')
		i++;
	while (line[i] == '|' || line[i] == '&')
	{
		operator[start][j++] = line[i++];
	}
	if (j)
		operator[start][j++] = '\0';
	return (slice);
}
