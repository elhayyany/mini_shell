/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:15:42 by akaouan           #+#    #+#             */
/*   Updated: 2022/08/09 16:09:41 by ael-hayy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_var_val	*get_pwd(t_list *elem, char *to_found)
{
	while (elem)
	{
		if (!ft_strncmp(((t_var_val *)(elem->content))->var,
			to_found, ft_strlen(to_found)) &&
			ft_strlen(to_found) == \
			ft_strlen(((t_var_val *)(elem->content))->var))
			return (((t_var_val *)(elem->content)));
		else
			elem = elem->next;
	}
	return (NULL);
}

void	update_env_pwd(t_var_val *pwd, t_var_val *old_pwd, char *path)
{
	char	*to_free;

	to_free = getcwd(NULL, 0);
	if (old_pwd && pwd)
	{
		free(old_pwd->value);
		if (!ft_strncmp(path, ".", 1) && ft_strlen(path) == 1)
			old_pwd->value = ft_strdup(to_free);
		else
			old_pwd->value = ft_strdup(pwd->value);
	}
	if (pwd)
	{
		free(pwd->value);
		pwd->value = ft_strdup(to_free);
	}
	free(to_free);
}

int	check_args(char *path, t_list *env_list, int output, t_var_val *home)
{
	t_var_val	*pwd;
	t_var_val	*old_pwd;

	pwd = get_pwd(env_list, "PWD");
	old_pwd = get_pwd(env_list, "OLDPWD");
	if (!path && home)
	{
		chdir(home->value);
		return (1);
	}
	else if (!home && !path)
	{
		ft_putendl_fd("minishell(v4.6): cd: HOME not set", output);
		return (1);
	}
	if (old_pwd && !ft_strncmp(path, "-", 1) && ft_strlen(path) == 1)
	{
		chdir(old_pwd->value);
		update_env_pwd(pwd, old_pwd, old_pwd->value);
		return (1);
	}
	else if (!old_pwd && !ft_strncmp(path, "-", 1) && ft_strlen(path) == 1)
		return (error(output, "minishell(v4.6): cd: OLDPWD not set", 0));
	return (0);
}

void	cd_error(char *path)
{
	ft_putstr_fd("cd: no such file or directory: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	cmd_cd(t_exec_elems *elems, char *path)
{
	t_var_val	*old_pwd;

	old_pwd = get_pwd(elems->env_elems->env_list, "OLDPWD");
	if (check_args(path, elems->env_elems->env_list, elems->cmd_output,
			get_pwd(elems->env_elems->env_list, "HOME")))
		return ;
	if (chdir(path) == -1)
	{
		cd_error(path);
		g_global.exit_status = 1;
		return ;
	}
	if (!old_pwd && g_global.rp)
	{
		ft_lstadd_back(&elems->env_elems->env_list,
			ft_lstnew(get_var_value("OLDPWD=no")));
		old_pwd = (t_var_val *)ft_lstlast(elems->env_elems->env_list)->content;
		free(old_pwd->value);
		old_pwd->value = NULL;
		g_global.rp = 0;
	}
	g_global.rp = 0;
	g_global.exit_status = 0;
	update_env_pwd(get_pwd(elems->env_elems->env_list, "PWD"),
		old_pwd, path);
}
