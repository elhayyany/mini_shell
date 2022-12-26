/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 09:50:24 by ael-hayy          #+#    #+#             */
/*   Updated: 2022/06/12 10:46:56 by ael-hayy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	cmd_free_i(t_cmd *cmd)
{
	if (cmd->filesin)
		free_db_str(cmd->filesin);
	if (cmd->filesout)
		free_db_str(cmd->filesout);
	if (cmd->fd)
		free(cmd->fd);
	if (cmd->her_doc)
		free(cmd->her_doc);
	if (cmd->inputs)
		free(cmd->inputs);
	if (cmd->write_to)
		free(cmd->write_to);
	if (cmd->read_from)
		free(cmd->read_from);
	if (cmd->outputs_num)
		free(cmd->outputs_num);
	if (cmd->outputs)
		free(cmd->outputs);
	if (cmd->lastout)
		free(cmd->lastout);
	if (cmd->lastin)
		free(cmd->lastin);
	if (cmd->inputs_num)
		free(cmd->inputs_num);
}

void	cmd_free(t_cmd *cmd)
{
	if (cmd->append_num)
		free(cmd->append_num);
	if (cmd->a)
		free(cmd->a);
	if (cmd->appends)
		free(cmd->appends);
	if (cmd->cmd)
		free(cmd->cmd);
	if (cmd->args)
		free_db_str(cmd->args);
	if (cmd->env_valuue)
		free_db_str(cmd->env_valuue);
	if (cmd->env_var)
		free_db_str(cmd->env_var);
	if (cmd->her_limit)
		free_db_str(cmd->her_limit);
	if (cmd->files_appends)
		free_db_str(cmd->files_appends);
	cmd_free_i(cmd);
}

int	free_tree_i(t_prior *script)
{
	int	j;

	j = 0;
	if (script->numofchilds == 0)
	{
		while (script->slices && script->slices[j])
		{
			free(script->slices[j]);
			j++;
		}
		free(script->slices[j]);
		free(script->slices);
		cmd_free(script->cmd);
		free(script->cmd);
		return (1);
	}
	j = 0;
	while (script->operator && script->operator[j])
	{
		free(script->operator[j]);
		j++;
	}
	free(script->operator[j]);
	free(script->operator);
	return (0);
}

void	free_tree(t_prior *script)
{
	int	j;

	if (free_tree_i(script))
		return ;
	j = 0;
	while (script->slices && script->slices[j])
	{
		free(script->slices[j]);
		j++;
	}
	free(script->slices[j]);
	free(script->slices);
	j = 0;
	while (j < script->numofchilds)
	{
		free_tree(script->next[j]);
		j++;
	}
	j = 0;
	while (j < script->numofchilds)
	{
		free(script->next[j]);
		j++;
	}
	free(script->next);
}
