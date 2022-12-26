/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaouan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:15:53 by akaouan           #+#    #+#             */
/*   Updated: 2022/08/01 11:15:56 by akaouan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_option(char *args)
{
	int	i;

	i = 0;
	if (!args)
		return (0);
	if (args[0] == '-' && args[1])
	{
		while (args[++i])
		{
			if (args[i] != 'n')
				return (0);
		}
		return (1);
	}
	return (0);
}

void	cmd_echo(int fd_output, char **args)
{
	int	i;
	int	option;

	i = 0;
	if (!args[0])
	{
		ft_putendl_fd("", fd_output);
		return ;
	}
	while (is_option(args[i]))
		i++;
	option = i;
	if (!args[i])
		return ;
	while (1)
	{
		ft_putstr_fd(args[i++], fd_output);
		if (args[i])
			ft_putchar_fd(' ', fd_output);
		else
			break ;
	}
	if (!option)
		ft_putchar_fd('\n', fd_output);
	g_global.exit_status = 0;
}
