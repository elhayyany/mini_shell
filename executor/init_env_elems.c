/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_elems.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaouan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 18:02:23 by akaouan           #+#    #+#             */
/*   Updated: 2022/07/31 18:02:24 by akaouan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_index(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i);
	return (i);
}

t_var_val	*get_var_value(char *env)
{
	t_var_val	*elem;

	elem = malloc(sizeof(t_var_val));
	if (!elem)
	{
		ft_putstr_fd("Faild to allocate memory\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	elem->value = ft_strdup(ft_strchr(env, '=') + 1);
	elem->var = ft_substr(env, 0, get_index(env, '='));
	return (elem);
}

void	init_env_list(t_list **env_list, char **env, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		if (ft_strncmp(env[i], "OLDPWD", 6))
			ft_lstadd_back(env_list, ft_lstnew(get_var_value(env[i])));
	}
}

void	init_env(t_env **env_elems, char **env)
{
	int	env_size;

	g_global.b_last = 0;
	env_size = arr_len(env);
	*env_elems = malloc(sizeof(t_env));
	(*env_elems)->env_list = NULL;
	if (!(*env_elems))
	{
		ft_putstr_fd("Faild to allocate memory\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	init_env_list(&(*env_elems)->env_list, env, env_size);
	(*env_elems)->env = env;
	g_global.rp = 1;
}
