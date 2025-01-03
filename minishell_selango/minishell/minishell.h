#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>
#include "parsing.h"


typedef struct s_env
{
	char *key;
	char *value;
	struct s_env    *next;
}               t_env;

typedef struct s_minishell
{
	char **environment;
	t_env *envlist;
	int ministdin;
	int ministdout;
	char *line;
	int exit_str;
	t_token			*tokens;
	t_token			*current_token;
	t_pars_error	pars_error;
	t_node			*ast;
	struct termios	terminal_settings;
	bool			heredoc_sigint;
	bool			sigint_child;
}               t_minishell;

/*ENUM types are user defined types .*Used to assign names to integral constants.
*enum names are automatically initialized by the compiler.*unsigned names are automatically initialized with the following increment.
(eg :ENO_CMD_LINE_INTERPRETER is not initialized so it is 127 because the previous value is 126 )
for the error number*/
typedef enum e_error_num
{
	ENO_SUCCESS,
	ENO_GENERAL,
	ENO_CMD_NOT_EXECUTABLE = 126,
	ENO_CMD_LINE_INTERPRETER,
	EN0_EXEC_ERROR = 255
} t_error_num;

/*enum ->enumeration struct for the error_msg*/
typedef enum e_error_msg
{
	ERR_CMD_NOT_FOUND,
	ERR_NO_SUCH_FILE,
	ERR_PERMISSION_DENIED,
	ERR_UNCLEAR,
	ERR_TOO_MANY_ARGUMENTS,
	ERR_NUMERIC_REQUIRED
} t_error_msg;
/*ast direction*/
typedef enum e_ast_direction
{
	TD_LEFT,
	TD_RIGHT
}	t_ast_direction

/*error msg struct*/
typedef struct 	s_error
{
	t_error_num 	no;
	t_error_msg msg;
	char *report;
}	t_error;
/*env path variable*/
typedef struct env_s_path
{
	t_error error;
	char *path;
}	env_t_path;

extern t_minishell minishell_global;

// environent settings

char set_key(char *str);
char set_value(char *str);
void envlist_initialization(void);
int ft_env(void);

//env_utilis
void *ft_garbage_collector(void *ptr,bool clean);
void envlist_add_to_back(t_env *new);
void envlist_updating (char *key, char *value, bool flag);
/*----------builtin function-----------*/
//cd  fn
int ft_cd(char *path);
//cd_utilis
char *ft_search_envlist(char *key);
int error_msg(char *err_msg);
//echo  fn
int ft_echo(char **argv);
//pwd  fn
int	ft_pwd(void);
//exit fn
void ft_exit(char **argv);
//export fn
int ft_valid(char *str);
int ft_export(char **argv);
//unset fn
int ft_unset(char **argv);


/*-------------------------------------execution fn-----------------*/
/*-----error_msg----------*/
int ft_error_msg(t_error err);

/*----------default execution------ */
bool default_checker(char **argv);
int ft_default_exec(char **argv);
/*---- Path_execution-----*/
env_t_path ft_env_path(char *path,char *cmd);
env_t_path ft_get_exec_path(char *cmd);
/*------ft_check_permission------*/
t_error ft_exec_check(char *file,bool cmd);
t_error ft_read_check(char *file);
t_error ft_write_check(char *file);
/*-------execution_pipe-------*/
int get_signal_status(int status);
int ft_exec_branch(t_node *branchtree,bool pipe);
/*--------redirect_execution---------*/
int ft_output_redirect(t_io_node *io_list,int * status,bool is_append);
int ft_input_redirect(t_io_node *io_list,int *status);
/*--------simple_cmd_execution-------*/
int redirect_exec_check(t_node *node);
void ft_reset_state(bool pipe);
int simple_cmd(t_node *node ,bool pipe);


/*-----cleaning environment-----*/
void ft_clear_msg();



#endif
