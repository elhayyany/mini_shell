/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buid_in_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 22:25:00 by akaouan           #+#    #+#             */
/*   Updated: 2022/08/09 17:08:29 by ael-hayy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_cd_pwd(t_exec_elems *elems)
{
	char	*to_free;

	to_free = NULL;
	if (!ft_strncmp(elems->args[0], "cd", 2) && ft_strlen(elems->args[0]) == 2)
	{
		if (elems->cmd_index == elems->size - 1)
			g_global.b_last = 1;
		cmd_cd(elems, elems->args[1]);
		elems->build_in = 1;
		return (1);
	}
	else if (!ft_strncmp(elems->args[0], "pwd", 3)
		&& ft_strlen(elems->args[0]) == 3)
	{
		if (elems->cmd_index == elems->size - 1)
			g_global.b_last = 1;
		to_free = getcwd(NULL, 0);
		error(elems->cmd_output, to_free, 1);
		free(to_free);
		g_global.exit_status = 0;
		elems->build_in = 1;
		return (1);
	}
	return (0);
}

int	check_echo_env_export(t_exec_elems *elems)
{
	if (!ft_strncmp(elems->args[0], "echo", 4)
		&& ft_strlen(elems->args[0]) == 4)
	{
		if (elems->cmd_index == elems->size - 1)
			g_global.b_last = 1;
		cmd_echo(elems->cmd_output, elems->args + 1);
		elems->build_in = 1;
		return (1);
	}
	else if (!ft_strncmp(elems->args[0], "env", 3)
		&& ft_strlen(elems->args[0]) == 3)
	{
		cmd_env(elems);
		return (1);
	}
	else if (!ft_strncmp(elems->args[0], "export", 6)
		&& ft_strlen(elems->args[0]) == 6)
	{
		if (elems->cmd_index == elems->size - 1)
			g_global.b_last = 1;
		cmd_export(&elems->env_elems->env_list, elems->args, elems);
		elems->build_in = 1;
		return (1);
	}
	return (0);
}

int	check_unset_exit(t_exec_elems *elems)
{
	if (!ft_strncmp(elems->args[0], "unset", 5)
		&& ft_strlen(elems->args[0]) == 5)
	{
		if (elems->cmd_index == elems->size - 1)
			g_global.b_last = 1;
		cmd_unset(&elems->env_elems->env_list, elems->args);
		elems->build_in = 1;
		return (1);
	}
	else if (!ft_strncmp(elems->args[0], "exit", 4)
		&& ft_strlen(elems->args[0]) == 4)
	{
		if (elems->cmd_index == elems->size - 1)
			g_global.b_last = 1;
		ft_exit(elems->args, elems);
		return (1);
	}
	return (0);
}

int	check_build_in(t_exec_elems *elems)
{
	if (check_cd_pwd(elems))
		return (1);
	else if (check_echo_env_export(elems))
		return (1);
	else if (check_unset_exit(elems))
		return (1);
	else
	{
		elems->build_in = 0;
		return (0);
	}
}
