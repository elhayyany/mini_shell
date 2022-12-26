/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_parser_iv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 17:30:25 by ael-hayy          #+#    #+#             */
/*   Updated: 2022/08/01 09:30:59 by ael-hayy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/minishell.h"

char	*get_quotesd_word(char *str)
{
	int		i;
	int		j;
	char	*tem;

	i = 1;
	j = 0;
	while (str[i] && str[i] != str[0])
		i++;
	tem = malloc(sizeof(char) * i + 1);
	while (j < i)
	{
		tem[j] = str[j + 1];
		j++;
	}
	tem[j] = '\0';
	return (tem);
}

void	ft_concat(char *str1, char *str2, int *j)
{
	int	i;

	i = 0;
	while (str2[i])
	{
		str1[*j] = str2[i];
		(*j)++;
		i++;
	}
	free(str2);
}

void	remove_quotes_str_i(char *str, char *new_str, int *j, int *i)
{
	if (str[*i] == '\'')
	{
		(*i)++;
		while (str[*i] != '\'')
		{
			new_str[*j] = str[*i];
			(*j)++;
			(*i)++;
		}
	}
	else if (str[*i] == '"')
	{
		(*i)++;
		while (str[*i] != '"')
		{
			new_str[*j] = str[*i];
			(*j)++;
			(*i)++;
		}
	}
	else
	{
		new_str[*j] = str[*i];
		(*j)++;
	}
}

char	*remove_quotes_str(char *str, t_cmd *pipe, int f)
{
	int		len;
	int		i;
	int		j;
	char	*new_str;

	if (!str)
		return (str);
	str = get_val(str, pipe, 1, f);
	if (pipe->read_from[0] == -1)
		return (0);
	if (no_quote_found(str))
		return (str);
	len = len_without_quotes(str);
	new_str = malloc(sizeof(char) * len + 1);
	i = 0;
	j = 0;
	while (str[i])
	{
		remove_quotes_str_i(str, new_str, &j, &i);
		i++;
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

char	**remove_quotes(char **str, t_cmd *pipe, int f)
{
	int		i;
	int		j;
	char	**new_str;

	i = 0;
	if (!str)
		return (str);
	j = strsnums(str);
	new_str = malloc(sizeof(char *) * (j + 1));
	while (i < j)
	{
		new_str[i] = remove_quotes_str(str[i], pipe, f);
		if (pipe->read_from[0] == -1)
		{
			free(new_str[i]);
			free(new_str);
			free(str);
			return (0);
		}
		i++;
	}
	new_str[i] = 0;
	free(str);
	return (new_str);
}
