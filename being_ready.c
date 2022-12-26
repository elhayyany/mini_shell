/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   being_ready.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 22:44:45 by ael-hayy          #+#    #+#             */
/*   Updated: 2022/08/01 08:44:08 by ael-hayy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/minishell.h"

void	ft_srtuct_bzero(t_cmd *pipe)
{
	pipe->write_to = 0;
	pipe->a = 0;
	pipe->line = 0;
	pipe->cmd = 0;
	pipe->args = 0;
	pipe->inputs_num = 0;
	pipe->outputs_num = 0;
	pipe->append_num = 0;
	pipe->appends = 0;
	pipe->outputs = 0;
	pipe->inputs = 0;
	pipe->files_appends = 0;
	pipe->filesin = 0;
	pipe->filesout = 0;
	pipe->her_doc = 0;
	pipe->her_limit = 0;
	pipe->env_var = 0;
	pipe->env_valuue = 0;
	pipe->lastout = 0;
	pipe->lastin = 0;
	pipe->fd = 0;
	pipe->read_from = malloc(sizeof(int));
}

t_cmd	*cmd_parse(char *line, char **env, t_list *head)
{
	t_cmd	*pipe;
	int		j;

	pipe = malloc(sizeof(t_cmd));
	ft_srtuct_bzero(pipe);
	(void)env;
	pipe->line = line;
	set_env(pipe, head, head);
	pipe->inputs_num = malloc(sizeof(int));
	pipe->outputs_num = malloc(sizeof(int));
	pipe->append_num = malloc(sizeof(int));
	pipe->her_doc = malloc(sizeof(int));
	pipe->inputs_num[0] = 0;
	pipe->outputs_num[0] = 0;
	pipe->append_num[0] = 0;
	pipe->her_doc[0] = 0;
	j = redirections(pipe);
	if (j == -1)
		pipe->read_from[0] = -1;
	return (pipe);
}

void	tree_parser(t_prior *script, char **env, t_list *head)
{
	int	i;
	int	j;

	if (script->numofchilds == 0)
	{
		script->cmd = cmd_parse(script->slices[0], env, head);
		return ;
	}
	i = script->numofchilds;
	g_global.k = i;
	j = 0;
	while (j < i)
	{
		tree_parser(script->next[j], env, head);
		j++;
	}
}
