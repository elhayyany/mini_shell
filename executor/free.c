/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaouan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 18:02:31 by akaouan           #+#    #+#             */
/*   Updated: 2022/07/31 18:02:33 by akaouan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_path_elems(char **paths, char *cmd)
{
	int	i;

	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	free(cmd);
}

void	free_elems(t_exec_elems *elems)
{
	int	i;

	i = -1;
	if (elems)
	{
		while (++i < 2)
			free(elems->pipes[i]);
		if (elems->cmd_path)
			free(elems->cmd_path);
		free(elems->pipes);
		free(elems->pids);
		free(elems);
	}
}
