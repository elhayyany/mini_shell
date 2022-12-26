/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_parser_vi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 17:24:25 by ael-hayy          #+#    #+#             */
/*   Updated: 2022/08/01 09:31:44 by ael-hayy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/minishell.h"

int	no_quote_found(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (0);
		i++;
	}
	return (1);
}

int	len_without_quotes(char *str)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			c = str[i++];
			while (str[i] != c)
			{
				i++;
				j++;
			}
		}
		else
			j++;
		i++;
	}
	return (j);
}

int	its_int_and_char(char *str)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]))
			j = 1;
		else if (ft_isdigit(str[i]))
			k = 1;
		i++;
	}
	if (k && j)
		return (1);
	return (0);
}

char	*str_without_char(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (ft_isdigit(str[i]))
		i++;
	new_str = malloc(sizeof(char) * ft_strlen(&str[i]) + 1);
	while (str[i])
	{
		new_str[j] = str[i];
		i++;
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

char	*get_valuue(char *var, t_cmd *pipe)
{
	int		i;
	char	*str;

	i = 0;
	if (ft_isdigit(var[0]))
	{
		str = ft_strdup(&var[1]);
		free(var);
		return (str);
	}
	while (pipe->env_var[i])
	{
		if (!ft_strncmp(var, pipe->env_var[i], sizeof(var)))
		{
			free(var);
			return (ft_strdup(pipe->env_valuue[i]));
		}
		i++;
	}
	free(var);
	return (0);
}
