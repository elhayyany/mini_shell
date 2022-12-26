/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_vi.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 17:32:29 by ael-hayy          #+#    #+#             */
/*   Updated: 2022/08/07 15:31:15 by ael-hayy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/minishell.h"

int	redirectappend(t_cmd *pipe, int i)
{
	char	*file_name;
	int		j;

	i += 2;
	while (pipe->line[i] && pipe->line[i] == ' ')
		i++;
	i = get_file_name(pipe, i, &file_name);
	file_name = remove_quotes_str(file_name, pipe, 1);
	if (pipe->read_from[0] == -1)
		return (-1);
	pipe->append_num[0] += 1;
	j = open(file_name, O_RDWR | O_CREAT, 0777);
	if (j == -1)
	{
		printf("minishell(v4.6): %s: permission denied\n", file_name);
		g_global.exit_status = 1;
		pipe->read_from[0] = -1;
		free(file_name);
		return (-1);
	}
	close(j);
	push_back(&(pipe->files_appends), file_name);
	return (i);
}

int	redirectout(t_cmd *pipe, int i)
{
	char	*file_name;
	int		j;

	i++;
	while (pipe->line[i] && pipe->line[i] == ' ')
		i++;
	i = get_file_name(pipe, i, &file_name);
	file_name = remove_quotes_str(file_name, pipe, 1);
	if (pipe->read_from[0] == -1)
		return (-1);
	pipe->outputs_num[0] += 1;
	j = open(file_name, O_RDWR | O_CREAT, 0777);
	if (j == -1)
	{
		printf("minishell(v4.6): %s: permission denied\n", file_name);
		free(file_name);
		g_global.exit_status = 1;
		pipe->read_from[0] = -1;
		return (-1);
	}
	close(j);
	push_back(&(pipe->filesout), file_name);
	return (i);
}

int	cmd_and_args(t_cmd *pipe, int i)
{
	char	*word;

	while (pipe->line[i] && pipe->line[i] == ' ')
		i++;
	i = get_file_name(pipe, i, &word);
	if (!pipe->cmd)
	{
		push_back(&(pipe->args), ft_strdup(word));
		pipe->cmd = word;
	}
	else
		push_back(&(pipe->args), word);
	return (i);
}

int	iterate_i(t_cmd *pipe, int *i)
{
	if (pipe->line[*i] == '<' && pipe->line[*i + 1] == '<')
	{
		pipe->lastout[0] = 1;
		*i = her_doc(pipe, *i);
		if (*i == -1)
			return (-1);
		return (1);
	}
	else if (pipe->line[*i] == '<' && pipe->line[*i + 1] != '<')
	{
		pipe->lastout[0] = 2;
		*i = redirectinp(pipe, *i);
		if (*i == -1)
			return (-1);
		return (1);
	}
	else if (pipe->line[*i] == '>' && pipe->line[*i + 1] == '>')
	{
		pipe->lastin[0] = 1;
		*i = redirectappend(pipe, *i);
		if (*i == -1)
			return (-1);
		return (1);
	}
	return (0);
}

int	iterate(t_cmd *pipe)
{
	int	i;
	int	j;

	i = 0;
	while (pipe->line[i])
	{
		j = iterate_i(pipe, &i);
		if (j == -1)
			return (-1);
		else if (j == 1)
			continue ;
		else if (pipe->line[i] == '>' && pipe->line[i + 1] != '>')
		{
			pipe->lastin[0] = 2;
			i = redirectout(pipe, i);
			if (i == -1)
				return (-1);
		}
		else if (pipe->line[i] != ' ')
			i = cmd_and_args(pipe, i);
		else if (pipe->line[i] == ' ')
			i++;
	}
	return (0);
}
