/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 10:17:05 by ael-hayy          #+#    #+#             */
/*   Updated: 2022/0 8/01 11:16:12 by akaouan          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	all_are_digit(char *args, int *j)
{
	int	i;

	i = 0;
	if (!args)
		return (0);
	if (args[0] == '-' || args[0] == '+')
		i++;
	while (args[i])
	{
		if (!ft_isdigit(args[i]))
		{
			*j = -1;
			return (-1);
		}
		i++;
	}
	return (ft_atoi(args));
}

int	is_dgt(char *line)
{
	int	i;

	i = 0;
	if (line[i] == '+' || line[i] == '+')
		i++;
	while (line[i])
	{
		if (ft_isdigit(line[i]))
			return (1);
		i++;
	}
	return (0);
}

void	exit_i(char **args)
{
	if (!g_global.con)
		printf("exit\nminishell: exit: %s: numeric argument required", \
		args[1]);
	else
		printf("minishell: exit: %s: numeric argument required", args[1]);
	g_global.exit_status = 1;
	if (!g_global.k)
		exit(255);
}

int	ft_exit(char **args, t_exec_elems *elems)
{
	int	is;
	int	a;

	is = 0;
	elems->build_in = 1;
	while (args[is + 1])
		is++;
	if (is == 0 && !g_global.k)
	{
		printf("exit\n");
		exit (0);
	}
	if (is > 1 && is_dgt(args[1]))
	{
		g_global.exit_status = 1;
		return (printf("exit\nminishell: exit: too many arguments\n"));
	}
	a = all_are_digit(args[1], &is);
	if (is == -1)
		exit_i(args);
	if (!g_global.con)
		printf("exit\n");
	if (!g_global.k)
		exit(a);
	return (0);
}
