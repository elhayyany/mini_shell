/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:37:45 by ael-hayy          #+#    #+#             */
/*   Updated: 2022/08/05 15:30:35 by ael-hayy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft/libft.h"
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>

typedef struct parsing
{
	int		*write_to;
	int		*read_from;
	int		*a;
	char	*line;
	char	*cmd;
	char	**args;
	int		*inputs_num;
	int		*outputs_num;
	int		*append_num;
	int		*appends;
	int		*outputs;
	int		*inputs;
	char	**files_appends;
	char	**filesin;
	char	**filesout;
	int		*her_doc;
	char	**her_limit;
	char	**env_var;
	char	**env_valuue;
	int		*lastout;
	int		*lastin;
	int		*fd;
}			t_cmd;

typedef struct priorities
{
	t_cmd				*cmd;
	char				**slices;
	int					numofchilds;
	char				**operator;
	char				*line;
	struct priorities	**next;
}	t_prior;

int			pre_check_line(char *line);
t_prior		*m_shell_parser(char *line);
void		check_malloc(void *ptr, void **ptro, int i);
int			calulate_cmds(char *line);
int			strsnums(char	**slices);
void		free_tree(t_prior *script);
int			next_qoute(char *line, char c);
int			all_space(char *line);
int			strsnums(char **slices);
int			redirections(t_cmd *pipe);
void		push_back(char	***stack, char *word);
void		ft_srtuct_bzero(t_cmd *pipe);
char		*remove_quotes_str(char *str, t_cmd *pipe, int f);
void		free_db_str(char **str);
char		*get_val(char *str, t_cmd *pipe, int j, int f);
char		**remove_quotes(char **str, t_cmd *pipe, int f);
int			process_quotes(t_cmd *pipe);
void		files_open(t_cmd *pipe);
int			no_quote_found(char *str);
char		*change_vall(char *str, char *var, char c);
char		*variable(char *str, t_cmd *pipe, int f);
char		*get_next_line(void);
void		free_db_int(int **intg, int num);
int			check_dir_ii(char c);
char		*variable_i(char *tem, t_cmd *pipe, int f);
void		rl_replace_line(const char *str, int undo);
int			check_parentheses_i(char *line, int *i, int *j, int *k);
void		sig_handler_cs(int c);
void		sig_handler_cc(int c);
void		sig_manager(void);
void		check_malloc(void *p, void **ptr, int i);
int			strsnums(char **slices);
void		calulate_cmds_lens_o(char *line, int *i, int *k);
int			calulate_cmds(char *line);
int			closed_parentheses(char *line);
void		calulate_cmds_lens(char *line, int *arr);
char		**allocate(int *lens, int i);
int			enplusstar(int *len, int start);
char		*clean_slice(char *slice);
char		*get_substr_i(char *line, int *len, int start, char **operator);
void		get_substr_oi(char *line, int i, int start, char **operator);
char		*get_substr(char *line, int *len, int start, char **operator);
void		get_operators(char ***operators, char *line, int *lens, int i);
char		**ft_split_pro(char *line, char **operators);
char		*new_slice(char *slice, int i, int j);
char		*clear_it(char *slice);
void		m_shell(char **slices, t_prior *script);
t_prior		*m_shell_parser(char *line);
void		get_herdoc(t_cmd *pipe, int j, char *limit);
int			open_her_doc_i(t_cmd *pip, int i);
void		open_her_doc(t_cmd *pip);
char		*ft_strjoinn(char *s1, char const *s2);
void		open_output(t_cmd *pipe);
void		open_input(t_cmd *pipe);
void		open_append(t_cmd *pipe);
void		files_open(t_cmd *pipe);
void		read_write(t_cmd *pipe);
int			all_space(char *line);
int			check_parentheses_ii(char *line, int *i, int *j, int *k);
int			next_qoute(char *line, char c);
int			check_parentheses_i(char *line, int *i, int *j, int *k);
int			check_parentheses(char *line);
int			check_andor(char *line);
int			check_dir(char *line);
int			not_expand(char *line);
int			get_file_name(t_cmd *pipe, int i, char **word);
int			pre_check_line(char *line);
int			iterate(t_cmd *pipe);
int			redirectinp(t_cmd *pipe, int i);
int			her_doc(t_cmd *pipe, int i);
void		push_back(char	***stack, char *word);
void		free_db_int(int **intg, int num);
void		free_db_str(char **str);
char		*get_quotesd_word(char *str);
void		ft_concat(char *str1, char *str2, int *j);
char		*remove_quotes_str(char *str, t_cmd *pipe, int f);
void		remove_quotes_str_i(char *str, char *new_str, int *j, int *i);
char		**remove_quotes(char **str, t_cmd *pipe, int f);
int			no_quote_found(char *str);
int			len_without_quotes(char *str);
int			its_int_and_char(char *str);
char		*str_without_char(char *str);
char		*get_valuue(char *var, t_cmd *pipe);
char		*rm_dollar(char *str, char c);
char		*variable_i(char *tem, t_cmd *pipe, int f);
int			untill_char(char *str, char c);
char		*variable(char *str, t_cmd *pipe, int f);
int			untill_char_v(char *str, char c);
int			after_var(char *str, char c);
char		*change_vall(char *str, char *var, char c);
char		*get_val_i(char *str, int f, int *i, t_cmd *pipe);
char		*get_val_il(char *str, t_cmd *pipe, int *i, int f);
char		*get_val(char *str, t_cmd *pipe, int j, int f);
int			lenplusstar(int *len, int start);
char		*next_getv(char *str, int *i, int f, t_cmd *pipe);
#endif