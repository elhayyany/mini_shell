/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 22:41:29 by ael-hayy          #+#    #+#             */
/*   Updated: 2022/08/01 09:29:56 by ael-hayy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/minishell.h"

int	lenuntillequal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

int	lenafterequal(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		i++;
	while (str[i++])
		j++;
	return (j);
}

void	set_env_v(t_cmd *pipe, int i, t_list *headtem)
{
	int	j;
	int	l;
	int	k;

	j = ft_strlen(((t_var_val *)headtem->content)->var);
	pipe->env_var[i] = (malloc(sizeof(char) * (j + 1)));
	k = 0;
	while (k < j)
	{
		pipe->env_var[i][k] = ((t_var_val *)headtem->content)->var[k];
		k++;
	}
	pipe->env_var[i][k] = '\0';
	j = ft_strlen(((t_var_val *)headtem->content)->value);
	pipe->env_valuue[i] = (malloc(sizeof(char) * (j + 1)));
	l = 0;
	k++;
	while (l < j)
	{
		if (((t_var_val *)headtem->content)->value)
			pipe->env_valuue[i][l] = ((t_var_val *)headtem->content)->value[l];
		l++;
		k++;
	}
	pipe->env_valuue[i][l] = '\0';
}

void	set_env(t_cmd *pipe, t_list *head, t_list *headtem)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (headtem)
	{
		headtem = headtem->next;
		i++;
	}
	pipe->env_var = malloc(sizeof(char *) * (i + 1));
	pipe->env_valuue = malloc(sizeof(char *) * (i + 1));
	i = 0;
	headtem = head;
	while (headtem)
	{
		set_env_v(pipe, i, headtem);
		i++;
		headtem = headtem->next;
	}
	pipe->env_var[i] = 0;
	pipe->env_valuue[i] = 0;
}
