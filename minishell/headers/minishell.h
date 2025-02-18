/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklimuk <mklimuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:37:16 by mklimuk           #+#    #+#             */
/*   Updated: 2024/12/17 14:37:16 by mklimuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stdlib.h>
# include "tokenization.h"
# include "parsing.h"
# include "libft.h"
# include <termios.h>
# include <signal.h>
# include <readline/history.h>
# include <fcntl.h>
# include <dirent.h>
# include <stdio.h>
# include <readline/readline.h>
# include <unistd.h>
# include <limits.h>
# include <sys/wait.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_minishell
{
	char			**environment;
	t_env			*envlist;
	int				ministdin;
	int				ministdout;
	char			*line;
	int				exit_s;
	t_token			*tokens;
	t_token			*current_token;
	t_pars_error	pars_error;
	t_node			*ast;
	struct termios	terminal_settings;
	bool			heredoc_sigint;
	bool			sigint_child;

}	t_minishell;

typedef enum e_error_msg
{
	ERR_CMD_NOT_FOUND,
	ERR_NO_SUCH_FILE,
	ERR_PERMISSION_DENIED,
	ERR_UNCLEAR,
	ERR_TOO_MANY_ARGUMENTS,
	ERR_NUMERIC_REQUIRED
}	t_error_msg;

typedef enum e_error_num
{
	ENO_SUCCESS,
	ENO_GENERAL,
	ENO_CMD_NOT_EXECUTABLE = 126,
	ENO_NOT_FOUND,
	ENO_EXEC_ERROR = 255
}	t_error_num;

typedef enum e_ast_direction
{
	TD_LEFT,
	TD_RIGHT
}	t_ast_direction;

typedef struct s_error
{
	t_error_num		no;
	t_error_msg		msg;
	char			*report;
}	t_error;

typedef struct s_env_path
{
	t_error	error;
	char	*path;
}	t_env_path;

/*----------builtin function-----------*/
int			ft_cd(char *path, t_minishell *minishell_variable);
char		*ft_search_envlist(char *key, t_minishell *minishell_variable);
int			error_msg(char *err_msg);
int			ft_echo(char **argv);
int			ft_pwd(t_minishell *minishell_variable);
void		ft_exit(char **argv, t_minishell *minishell_variable);
int			ft_valid(char *str);
int			ft_export(char **argv, t_minishell *minishell_variable);
int			ft_unset(char **argv, t_minishell *minishell_variable);
int			ft_str_isdigit(const char *str);

//Execution
int			ft_error_msg(t_error err);
bool		default_checker(char **argv);
int			ft_default_exec(char **argv, t_minishell	*minishell_variable);
t_env_path	env_error(char *cmd, char *command_path, bool success);
t_env_path	ft_env_path(char *path, char *cmd);
t_env_path	ft_get_exec_path(char *cmd, t_minishell *minishell_variable);
t_error		ft_exec_check(char *file, bool cmd);
t_error		ft_read_check(char *file);
t_error		ft_write_check(char *file);
int			get_signal_status(int status);
int			ft_exec_branch(t_node *tree, bool pipe,
				t_minishell *minishell_variable);
int			ft_output_redirect(t_io_node *io_list, int *status);
int			ft_input_redirect(t_io_node *io_list, int *status);
int			ft_append_redirect(t_io_node *io_list, int *status);
int			redirect_exec_check(t_node *node);
void		ft_reset_state(bool pipe, t_minishell *minishell_variable);
int			simple_cmd(t_node *node, bool pipe,
				t_minishell *minishell_variable);
void		heredoc_handler(t_io_node *io, int pfds[2],
				t_minishell *minishell_variable);
void		init_tree(t_node *node, t_minishell *minishell_variable);
bool		found_delimiter(char *delimiter, char *str);

/*----------expanders------------*/
char		*ft_dollar_handler(char *str, size_t *i,
				t_minishell *minishell_variable);
char		*ft_strjoin_free(char *s1, char *s2);
void		skip_words(char *str, size_t *i);
bool		ft_char_checker(char c);
char		*ft_normal_handler(char *str, size_t *i);
char		*ft_squotes_handler(char *str, size_t *i);
char		*ft_dquotes_handler(char *str, size_t *i,
				t_minishell *minishell_variable);
char		*ft_clear_empty_str(char *str);
char		**ft_expand(char *str, t_minishell *minishell_variable);
char		**ft_expander_split(char *str);
char		*ft_remove_quotes(char *str);
void		ft_heredoc_expander(char *input, int fd,
				t_minishell *minishell_variable);

// cleaners
// static void	envlist_cleaner(void);
void		clean_minishell(t_minishell *minishell_variable);
void		*ft_garbage_collector(void *ptr, bool clean);

// environent settings
char		*set_key(char *str);
char		*set_value(char *str);
void		envlist_updating(char *key, char *value,
				bool flag, t_minishell *minishell_variable);
void		envlist_initialization(t_minishell *minishell_variable);
int			ft_env(t_minishell *minishell_variable);
// signals
// static void	sigint_handler(int num);
void		sig_init(t_minishell *minishell_variable);
void		siquit_handler(int num);

// utils
t_env		*new_envlst(char *key, char *value);
void		envlist_add_to_back(t_env *new, t_minishell *minishell_variable);
t_minishell	*get_minishell_variable(void);
void		set_minishell_variable(t_minishell *new_minishell_variable);

#endif
