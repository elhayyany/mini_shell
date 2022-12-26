/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 18:02:51 by akaouan           #+#    #+#             */
/*   Updated: 2022/08/09 17:28:38 by ael-hayy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	wait_pids(t_exec_elems *elems)
{
	int	i;
	int	es;

	i = -1;
	if (!elems->pids[0])
		return ;
	while (++i < elems->size)
	{
		waitpid(elems->pids[i], &es, 0);
		if (!g_global.b_last)
			g_global.exit_status = WEXITSTATUS(es);
	}
}

int	check_cmd(char **paths, char *cmd)
{
	if (!access(cmd, F_OK))
	{
		if (paths)
			free_path_elems(paths, NULL);
		return (1);
	}
	else
		return (0);
}

char	*get_cmd_path(t_exec_elems *elems, char *cmd, char *path_value)
{
	int		i;
	char	*cmd_path;
	char	**paths;

	i = -1;
	cmd_path = NULL;
	paths = ft_split(path_value, ':');
	if (check_cmd(paths, cmd + 1))
		return (cmd);
	if (!paths)
		return (path_err(cmd, 1, 0));
	while (paths[++i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (!access(cmd_path, F_OK))
		{
			free_path_elems(paths, cmd);
			return (cmd_path);
		}
		free(cmd_path);
	}
	free_path_elems(paths, cmd);
	return (path_err(NULL, 0, elems->cmd_input));
}

int	arr_len(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}
