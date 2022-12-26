/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 09:50:09 by ael-hayy          #+#    #+#             */
/*   Updated: 2022/08/07 19:57:14 by ael-hayy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/minishell.h"

void	execution(t_prior *data, t_exec_elems *elems)
{
	int	j;
	int	i;

	j = 0;
	i = data->numofchilds;
	if (i == 0)
	{
		update_elems(elems, data);
		if (!elems->build_in)
			execute(elems);
		update_pipes(elems->pipes, elems->p2);
		return ;
	}
	while (j < i)
		j++;
	j = 0;
	while (j < i)
	{
		execution(data->next[j], elems);
		j++;
	}
}

void	free_it(t_exec_elems *elems, t_env *env_elems, t_prior *script)
{
	init_exec_elems(&elems, env_elems, script->numofchilds);
	execution(script, elems);
	close_pipes(elems->pipes);
	wait_pids(elems);
	g_global.k = 0;
	free_elems(elems);
}

void	set_def(t_env **env_elems, char **env)
{
	sig_manager();
	g_global.her = 0;
	init_env(env_elems, env);
}

int	ft_readline(char **line)
{
	g_global.dlr_num = 0;
	if (g_global.her == -1)
	{
		g_global.her = 0;
		dup2(g_global.saver, 0);
	}
	g_global.is = 0;
	*line = readline("\033[0;32mminishell(v4.6)$> \033[0m");
	if ((*line) && (*line)[0])
		add_history((*line));
	if (!(*line))
		exit(0);
	if (!all_space((*line)) || pre_check_line((*line)))
	{
		free((*line));
		return (1);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char			*line;
	t_prior			*script;
	t_exec_elems	*elems;
	t_env			*env_elems;

	elems = 0;
	env_elems = 0;
	(void)ac;
	(void)av;
	set_def(&env_elems, env);
	while (1)
	{
		if (ft_readline(&line))
			continue ;
		script = m_shell_parser(line);
		tree_parser(script, env, env_elems->env_list);
		g_global.is = 1;
		if (g_global.her != -1)
			free_it(elems, env_elems, script);
		free_tree(script);
		free(script);
		free (line);
		line = 0;
	}
}
