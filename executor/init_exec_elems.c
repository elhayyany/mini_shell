/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec_elems.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 18:02:07 by akaouan           #+#    #+#             */
/*   Updated: 2022/08/09 17:31:07 by ael-hayy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_pipes(t_exec_elems *elems)
{
	if (elems->cmd_input < 2 && elems->cmd_input > -1)
		elems->cmd_input = elems->pipes[elems->p1][0];
	if (elems->cmd_output < 2 && elems->cmd_output > -1)
		elems->cmd_output = elems->pipes[elems->p2][1];
	swap(&elems->p1, &elems->p2);
}

char	*init_cmd_path(t_exec_elems *elems, char *cmd)
{
	char	*cmd_path;
	char	*path;
	t_list	*env_list;

	env_list = elems->env_elems->env_list;
	path = NULL;
	while (env_list)
	{
		if (!ft_strncmp(((t_var_val *)env_list->content)->var
				, "PATH", 4))
		{
			path = ((t_var_val *)env_list->content)->value;
			break ;
		}
		env_list = env_list->next;
	}
	cmd_path = get_cmd_path(elems, ft_strjoin("/", cmd), path);
	if (!cmd_path)
	{
		elems->build_in = 2;
		elems->cmd_index++;
	}
	return (cmd_path);
}

void	update_elems(t_exec_elems *elems, t_prior *data)
{
	elems->cmd_input = data->cmd->read_from[0];
	if (data->cmd->write_to)
		elems->cmd_output = data->cmd->write_to[0];
	else
		elems->cmd_output = 1;
	elems->args = data->cmd->args;
	free(elems->cmd_path);
	elems->cmd_path = NULL;
	if (elems->size > 1
		&& elems->cmd_index > 0 && elems->cmd_index < elems->size - 1)
		set_pipes(elems);
	else if (elems->size > 1 && !elems->cmd_index && elems->cmd_output < 2
		&& elems->cmd_output > -1)
		elems->cmd_output = elems->pipes[elems->p1][1];
	else if (elems->size > 1 && elems->cmd_input < 2 && elems->cmd_input > -1)
		elems->cmd_input = elems->pipes[elems->p1][0];
	if (data->cmd->cmd
		&& (data->cmd->cmd[0] == '.' && data->cmd->cmd[1] == '/'))
		elems->cmd_path = ft_strdup(data->cmd->cmd);
	else if (data->cmd->cmd && check_build_in(elems))
		elems->cmd_index++;
	else
		elems->cmd_path = init_cmd_path(elems, data->cmd->cmd);
}

int	init_pipes(int **pipes)
{
	int	i;

	i = -1;
	while (++i < 2)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			return (0);
		if (pipe(pipes[i]) == -1)
		{
			ft_putstr_fd("Faild to open pipes\n", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
	}
	return (1);
}

void	init_exec_elems(t_exec_elems **elems
			, t_env *env_elems, int size)
{
	if (!size)
		size++;
	*elems = malloc(sizeof(t_exec_elems));
	(*elems)->pids = malloc((sizeof(int) * size));
	(*elems)->pipes = malloc(sizeof(int *) * 2);
	if (!(*elems)
		|| !(*elems)->pids || !(*elems)->pipes
		|| !init_pipes((*elems)->pipes))
	{
		ft_putstr_fd("Faild to allocate memory\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	(*elems)->i_pid = 0;
	(*elems)->cmd_index = 0;
	(*elems)->p1 = 0;
	(*elems)->p2 = 1;
	(*elems)->build_in = 0;
	(*elems)->size = size;
	(*elems)->args = NULL;
	(*elems)->cmd_path = NULL;
	(*elems)->env_elems = env_elems;
	g_global.elems = *elems;
}
