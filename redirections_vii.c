/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_vii.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 17:33:31 by ael-hayy          #+#    #+#             */
/*   Updated: 2022/08/09 16:07:52 by ael-hayy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/minishell.h"

void	free_db_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str[i]);
	free(str);
}

void	free_db_int(int **intg, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		free(intg[i]);
		i++;
	}
	free(intg);
}

void	push_back(char	***stack, char *word)
{
	int		i;
	char	**newstack;

	if (!(*stack))
	{
		*stack = malloc(sizeof(char *) * 2);
		(*stack)[0] = word;
		(*stack)[1] = 0;
	}
	else
	{
		i = strsnums(*stack);
		newstack = malloc(sizeof(char *) * (i + 2));
		i = 0;
		while ((*stack)[i])
		{
			newstack[i] = ft_strdup((*stack)[i]);
			i++;
		}
		newstack[i] = word;
		i++;
		newstack[i] = NULL;
		free_db_str(*stack);
		(*stack) = newstack;
	}
}

int	her_doc(t_cmd *pipe, int i)
{
	char	*limiter;

	i += 2;
	while (pipe->line[i] && pipe->line[i] == ' ')
		i++;
	i = get_file_name(pipe, i, &limiter);
	pipe->her_doc[0] += 1;
	push_back(&(pipe->her_limit), limiter);
	return (i);
}

int	redirectinp(t_cmd *pipe, int i)
{
	char	*file_name;

	i++;
	while (pipe->line[i] && pipe->line[i] == ' ')
		i++;
	i = get_file_name(pipe, i, &file_name);
	file_name = remove_quotes_str(file_name, pipe, 1);
	if (pipe->read_from[0] == -1)
		return (-1);
	pipe->inputs_num[0] += 1;
	if (access(file_name, F_OK) == -1 || access(file_name, R_OK) == -1)
	{
		if (access(file_name, F_OK) == -1)
			printf("minishell(v4.6): %s:  No such file or directory\n", \
			file_name);
		else
			printf("minishell(v4.6): %s:  permission denied:\n", file_name);
		g_global.exit_status = 1;
		free(file_name);
		return (-1);
	}
	push_back(&(pipe->filesin), file_name);
	return (i);
}
