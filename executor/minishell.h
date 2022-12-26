/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:21:28 by ael-hayy          #+#    #+#             */
/*   Updated: 2022/08/09 17:28:26 by ael-hayy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../parser.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>

typedef struct n_var_val{
	char	*var;
	char	*value;
}	t_var_val;

typedef struct n_env{
	t_list		*env_list;
	char		**env;
}	t_env;

typedef struct n_exec_elems{
	int		build_in;
	t_env	*env_elems;
	char	*cmd_path;
	char	**args;
	int		**pipes;
	int		*pids;
	int		i_pid;
	int		p1;
	int		p2;
	int		size;
	int		cmd_index;
	int		cmd_input;
	int		cmd_output;

}	t_exec_elems;

typedef struct jp_morgan
{
	int				exit_status;
	int				is;
	int				con;
	int				is_printed;
	int				her;
	int				saver;
	int				k;
	int				dlr_num;
	int				b_last;
	int				rp;
	t_exec_elems	*elems;
}	t_jp;

t_jp	g_global;

void		wr_error(int fd, char *err_msg, int i);
void		execute(t_exec_elems *elems);
void		wait_pids(t_exec_elems *elems);
void		init_exec_elems(t_exec_elems **elems,
				t_env *env_elems, int size);
void		update_elems(t_exec_elems *elems, t_prior *data);
char		*get_cmd_path(t_exec_elems *elems, char *cmd, char *env_values);
int			get_path_index(char **env_vars);
void		swap(int *a, int *b);
void		close_pipes(int	**pipes);
void		update_pipes(int **pipes, int to_close);
void		cmd_cd(t_exec_elems *elems, char *path);
void		cmd_echo(int fd_output, char **args);
void		free_exec_elems(t_exec_elems *elems);
void		init_env(t_env **env_elems, char **env);
char		**get_env_values(char **env, int env_size);
char		**get_env_vars(char **env, int env_size);
int			arr_len(char **arr);
int			check_build_in(t_exec_elems *elems);
void		cmd_env(t_exec_elems *elems);
int			check_build_in(t_exec_elems *elems);
int			cmd_export(t_list **env_list, char **args, t_exec_elems *elems);
int			get_index(char *str, char c);
void		cmd_unset(t_list **env_list, char **args);
void		free_elems(t_exec_elems *elems);
void		delete_var_val(t_list **env_list, char *arg);
void		tree_parser(t_prior *script, char **env, t_list *head);
void		set_env(t_cmd *pipe, t_list *head, t_list *headtem);
int			ft_exit(char **args, t_exec_elems *elems);
void		free_path_elems(char **paths, char *cmd);
void		pwd_print(t_list *env_list, int output);
void		print_error(char *var, char *val);
t_var_val	*get_var_value(char *env);
int			error(int output, char *error_msg, int i);
t_var_val	*get_pwd(t_list *elem, char *to_found);
int			check_var_val(t_list *env_list, char *var, char *val);
char		*path_err(char *cmd, int i, int input);
#endif
