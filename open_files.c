/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:09:49 by ael-hayy          #+#    #+#             */
/*   Updated: 2022/08/07 15:31:15 by ael-hayy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/minishell.h"

void	open_input(t_cmd *pipe)
{
	int	i;

	i = 0;
	if (!pipe->filesin)
		return ;
	pipe->inputs = malloc(strsnums(pipe->filesin) * sizeof(int));
	while (pipe->filesin[i])
	{
		pipe->inputs[i] = open(pipe->filesin[i], O_RDONLY);
		if (pipe->inputs[i] == -1)
		{
			pipe->a[0] = -1;
			printf("minishell(v4.6): %s:", pipe->filesin[i]);
			printf("permission denied or file doesnt exitst\n");
			g_global.exit_status = 1;
			while (i-- > 0)
				close (pipe->inputs[i]);
			break ;
		}
		i++;
	}
	i--;
	while (i-- > 0)
		close (pipe->inputs[i]);
	pipe->a[0] = 1;
}

void	open_append(t_cmd *pipe)
{
	int	i;

	i = 0;
	if (!pipe->files_appends)
		return ;
	pipe->appends = malloc(strsnums(pipe->files_appends) * sizeof(int));
	while (pipe->files_appends[i])
	{
		pipe->appends[i] = open(pipe->files_appends[i], \
		O_RDWR | O_CREAT | O_APPEND);
		if (pipe->appends[i] == -1)
		{
			pipe->a[0] = -1;
			printf("minishell(v4.6): %s:", pipe->files_appends[i]);
			printf("permission denied or file doesnt exitst\n");
			pipe->read_from[0] = -1;
			g_global.exit_status = 1;
			while (i-- > 0)
				close (pipe->appends[i]);
			break ;
		}
		i++;
	}
	pipe->a[0] = 1;
}

void	read_write(t_cmd *pipe)
{
	pipe->write_to = malloc(sizeof(int));
	if (pipe->lastout[0] == 1)
		pipe->read_from[0] = pipe->fd[0];
	else if (pipe->lastout[0] == 2)
		pipe->read_from[0] = pipe->inputs[strsnums(pipe->filesin) - 1];
	else
		pipe->read_from[0] = 0;
	if (pipe->lastin[0] == 1)
		pipe->write_to[0] = pipe->appends[strsnums(pipe->files_appends) - 1];
	else if (pipe->lastin[0] == 2)
		pipe->write_to[0] = pipe->outputs[strsnums(pipe->filesout) - 1];
	else
		pipe->write_to[0] = 1;
}

void	files_open(t_cmd *pipe)
{
	if (pipe->read_from[0] != -1)
	{
		pipe->a = malloc(sizeof(int));
		open_her_doc(pipe);
		open_output(pipe);
		open_input(pipe);
		open_append(pipe);
		read_write(pipe);
		if (!pipe->cmd)
			pipe->read_from[0] = -1;
	}
}
