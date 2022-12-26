/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_parser_viii.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 17:29:03 by ael-hayy          #+#    #+#             */
/*   Updated: 2022/08/05 19:39:06 by ael-hayy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/minishell.h"

int	after_var(char *str, char c)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (c == '?')
		return (2);
	if (str[i] && (str[i] == '\'' || str[i] == '"'))
	{
		return (next_qoute(str, str[0]) + 2);
	}
	while (str[i] && (ft_isalpha(str[i]) \
	|| ft_isdigit(str[i]) || str[i] == '_'))
		i++;
	i++;
	return (i);
}

char	*change_vall(char *str, char *var, char c)
{
	int		j;
	char	*tem;
	char	*tem_t;
	char	*tem_tw;

	tem_t = str;
	j = untill_char_v(str, '$');
	tem = ft_substr(str, 0, j);
	j += after_var(&str[j + 1], c);
	tem_tw = ft_substr(str, j, ft_strlen(str));
	if (var)
		str = ft_strjoinn(tem, var);
	else
		str = tem;
	str = ft_strjoinn(str, tem_tw);
	if (var)
		free(var);
	if (tem_tw)
		free(tem_tw);
	free(tem_t);
	return (str);
}

char	*get_val_i(char *str, int f, int *i, t_cmd *pipe)
{
	char	*tem_tw;

	tem_tw = 0;
	if (*i != 0 && str[*i - 1] == '"' && str[*i + 1] == '"')
	{
	}
	else
	{
		tem_tw = variable(&str[*i + 1], pipe, f);
		if (f == 1 && !tem_tw)
		{
			pipe->read_from[0] = -1;
			write(2, "ambiguous redirect\n", 19);
			g_global.exit_status = 1;
			*i = -1;
			return (0);
		}
		str = change_vall(str, tem_tw, 'p');
		(*i)--;
	}
	return (tem_tw);
}

char	*get_val_il(char *str, t_cmd *pipe, int *i, int f)
{
	char	*tem_tw;

	if (str[(*i) + 1] == '?')
		str = change_vall(str, ft_itoa(g_global.exit_status), '?');
	else
	{
		if ((*i) != 0 && str[(*i) - 1] == '"' && str[(*i) + 1] == '"')
		{
		}
		else
		{
			tem_tw = variable(&str[(*i) + 1], pipe, f);
			if (f == 1 && !tem_tw)
			{
				pipe->read_from[0] = -1;
				write(2, "ambiguous redirect\n", 19);
				g_global.exit_status = 1;
				return (0);
			}
			str = change_vall(str, tem_tw, '\0');
			(*i)--;
		}
	}
	(*i) = -1;
	return (str);
}

char	*get_val(char *str, t_cmd *pipe, int j, int f)
{
	int		i;
	int		k;

	i = -1;
	k = 0;
	while (str[++i])
	{
		if (str[i] == '\"')
		{
			if (!k)
				k = 1;
			else
				k = 0;
		}
		if (j && str[i] == '\'' && !k)
			i += next_qoute(&str[i], '\'');
		if (str[i] == '$' && not_expand(&str[i + 1]))
		{
			k = 0;
			str = next_getv(str, &i, f, pipe);
			if (!str)
				return (0);
		}
	}
	return (str);
}
