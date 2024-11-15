#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdbool.h>
#include <readline/readline.h>

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


}               t_minishell;

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

//cd builtin fn
int ft_cd(char *path);
//cd_utilis
char *ft_search_envlist(char *key);
static int cd_error_msg(char *err_msg);
//

#endif