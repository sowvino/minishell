#include <minishell.h>

// I use ft_memset, but no malloc, becasue minishell_global has already been initialized in header. so I only need to fill it with zeroes.
// after ft_memset I know which values are sorted in minishell_global. it can prevent unexpected behaviour. Because random values can cause bugs.
// minishell_global.ministdin = dup(0); - redirecting file descriptor to ministdin
static void minishell_initialization(char **env)
{
	ft_memset(&minishell_global, 0, sizeof(t_minishell));
	minishell_global.environment = env;
	envlist_initialization();
	minishell_global.ministdin = dup(0);
	minishell_global.ministdout = dup(1);
	// tcgetattr(STDIN_FILENO, &minishell_global.original_term);

}

// env is an environmental variale. it contains a massive to system information such as PATH, USER, HOME and so on.
// it is stored as key-value pairs. OS uses it to behave properly. 
// those variables provide details about file's paths, user's information and so on.
// readline is for getting a user's input. PROMPT is what will be shown before user's input
int main(int argc, char **argv, char **env)
{
	 minishell_initialization(env);
	 while (1)
	 {
		// signals initialization
		minishell_global.line = readline(PROMPT);
	 }
}