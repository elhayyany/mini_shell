/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 18:02:03 by ael-hayy          #+#    #+#             */
/*   Updated: 2022/08/01 09:24:50 by ael-hayy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/minishell.h"

int	word_length(t_cmd *pipe, int i)
{
	int	j;

	j = 0;
	while (pipe->line[i])
	{
		if (pipe->line[i] == '\'' || pipe->line[i] == '\"')
		{
			j += next_qoute(&pipe->line[i], pipe->line[i]);
			i += next_qoute(&pipe->line[i], pipe->line[i]);
		}
		if (pipe->line[i] == ' ' || pipe->line[i] == '|' || pipe->line[i] == \
		'&' || pipe->line[i] == '<' || pipe->line[i] == '>')
		{
			return (j);
		}	
		i++;
		j++;
	}
	return (j);
}

int	get_file_name(t_cmd *pipe, int i, char **word)
{
	int	j;
	int	k;

	k = 0;
	j = word_length(pipe, i);
	(*word) = malloc(sizeof(char) * j + 1);
	while (k < j)
	{
		(*word)[k] = pipe->line[i];
		i++;
		k++;
	}
	(*word)[k] = '\0';
	return (i);
}

int	redirections(t_cmd *pipe)
{
	pipe->lastout = malloc(sizeof(int));
	pipe->lastin = malloc(sizeof(int));
	pipe->lastout[0] = 0;
	pipe->lastin[0] = 0;
	if (iterate(pipe) == -1)
		return (-1);
	process_quotes(pipe);
	files_open(pipe);
	return (1);
}
