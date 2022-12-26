/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signls.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 12:57:12 by ael-hayy          #+#    #+#             */
/*   Updated: 2022/08/01 17:24:12 by ael-hayy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/minishell.h"

void	sig_manager(void)
{
	signal(SIGINT, &sig_handler_cc);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_handler_cc(int c)
{
	int	i;

	i = -1;
	if (!g_global.is)
	{
		if (g_global.her)
		{
			g_global.her = -1;
			g_global.saver = dup(0);
			close(0);
			return ;
		}
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
	{
		while (++i < g_global.elems->size)
			if (g_global.elems->pids[i])
				kill(g_global.elems->pids[i], SIGKILL);
		printf("\n");
	}
	(void)c;
}
