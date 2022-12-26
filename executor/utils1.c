/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 16:14:24 by akaouan           #+#    #+#             */
/*   Updated: 2022/08/09 17:29:52 by ael-hayy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*path_err(char *cmd, int i, int input)
{
	if (!i)
	{
		if (input != -1)
			ft_putstr_fd("Couldn't found command\n", STDERR_FILENO);
		g_global.exit_status = 127;
		return (NULL);
	}
	ft_putendl_fd("set path", STDERR_FILENO);
	free(cmd);
	return (NULL);
}

int	error(int output, char *error_msg, int i)
{
	if (i)
	{
		if (error_msg)
			ft_putendl_fd(error_msg, output);
		else
		{
			ft_putstr_fd("cd: error retrieving current directory: getcwd:",
				output);
			ft_putstr_fd(" cannot access parent directories: No such", output);
			ft_putendl_fd(" file or directory", output);
		}
		return (1);
	}
	ft_putendl_fd(error_msg, output);
	return (1);
}

int	check_var_val(t_list *env_list, char *var, char *val)
{
	t_var_val	*env_var;

	env_var = get_pwd(env_list, var);
	if (env_var && env_var->value[0]
		&& (!val || (val[0] == '=' && *(val + 1) == '\0')))
	{
		free(var);
		free(val);
		return (1);
	}
	return (0);
}

void	pwd_print(t_list *env_list, int output)
{
	while (env_list)
	{
		if (!ft_strncmp(((t_var_val *)env_list->content)->var, "PWD", 3))
		{
			ft_putstr_fd(((t_var_val *)env_list->content)->value, output);
			ft_putchar_fd('\n', output);
			return ;
		}
		env_list = env_list->next;
	}
}
