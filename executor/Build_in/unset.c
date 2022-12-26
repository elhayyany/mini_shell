/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaouan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:16:40 by akaouan           #+#    #+#             */
/*   Updated: 2022/08/01 11:16:41 by akaouan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delete(void *elem)
{
	t_var_val	*to_free;

	to_free = (t_var_val *)elem;
	free(to_free->value);
	free(to_free->var);
	free(to_free);
}

void	delete_var_val(t_list **env_list, char *arg)
{
	t_list	*head;
	t_list	*before;
	char	*var;

	var = ft_substr(arg, 0, get_index(arg, '='));
	head = *env_list;
	before = NULL;
	while (head)
	{
		if (ft_strlen(((t_var_val *)head->content)->var) == ft_strlen(var)
			&& !ft_strncmp(((t_var_val *)head->content)->var,
				var, ft_strlen(var)))
		{
			if (!before)
				(*env_list) = (*env_list)->next;
			else
				before->next = head->next;
			ft_lstdelone(head, &delete);
			free(var);
			return ;
		}
		before = head;
		head = head->next;
	}
	free(var);
}

int	unset_is_valid(char *var)
{
	int	i;

	i = -1;
	if (ft_isdigit(var[0]) || var[0] == '=')
		return (0);
	while (var[++i])
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
	return (1);
}

void	cmd_unset(t_list **env_list, char **args)
{
	int	i;
	int	error;

	i = 1;
	error = 0;
	while (args[i])
	{
		if (unset_is_valid(args[i]))
			delete_var_val(env_list, args[i]);
		else
		{
			error = 1;
			print_error(args[i], NULL);
		}
		i++;
	}
	if (!error)
		g_global.exit_status = 0;
}
