/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 09:49:57 by ael-hayy          #+#    #+#             */
/*   Updated: 2022/08/05 19:38:39 by ael-hayy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/minishell.h"

int	not_expand(char *line)
{
	if (ft_isdigit(line[0]) || ft_isalpha(line[0]) \
	|| line[0] == '?' || line[0] == '_' || line[0] == '\'' || line[0] == '"')
		return (1);
	g_global.dlr_num++;
	return (0);
}

char	*next_getv(char *str, int *i, int f, t_cmd *pipe)
{
	if (str[(*i) + 1] != '\'')
	{
		str = get_val_il(str, pipe, i, f);
		if (!str)
			return (0);
	}
	return (str);
}

int	process_quotes(t_cmd *pipe)
{
	pipe->cmd = remove_quotes_str(pipe->cmd, pipe, 0);
	pipe->args = remove_quotes(pipe->args, pipe, 0);
	return (0);
}
