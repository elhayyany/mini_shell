/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaouan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:16:03 by akaouan           #+#    #+#             */
/*   Updated: 2022/08/01 11:16:05 by akaouan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_env(t_exec_elems *elems)
{
	t_list	*env_list;

	elems->build_in = 1;
	if (elems->cmd_index == elems->size - 1)
		g_global.b_last = 1;
	env_list = elems->env_elems->env_list;
	while (env_list)
	{
		if (((t_var_val *)env_list->content)->value
			&& ((t_var_val *)env_list->content)->value[0])
		{
			ft_putstr_fd(((t_var_val *)(env_list->content))->var,
				elems->cmd_output);
			ft_putchar_fd('=', elems->cmd_output);
			ft_putstr_fd(((t_var_val *)(env_list->content))->value,
				elems->cmd_output);
			ft_putchar_fd('\n', elems->cmd_output);
		}
		env_list = env_list->next;
	}
	g_global.exit_status = 0;
}
