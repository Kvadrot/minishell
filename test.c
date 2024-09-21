#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


typedef struct s_cmd {
    char *argv[10]; // Array to hold the command arguments
} t_cmd;

void handle_tokens(t_cmd *cmd, t_cmd **ret, char **ps, char *es);

void panic(char *msg) {
	printf("Error: %s\n", msg);
	exit(1);
}

// Mock versions of the external functions
int peek(char **ps, char *es, char *tokens) {
    // Simple mock that checks the current token for matching conditions
    return **ps && strchr(tokens, **ps);
}

int gettoken(char **ps, char *es, char **q, char **eq) {
    // Mock implementation to simulate token extraction
    if (*ps >= es)
        return 0; // No more tokens
    *q = *ps; // Set start of the token
    while (*ps < es && **ps != ' ' && **ps != '|') (*ps)++;
    *eq = *ps; // Set end of the token
    if (*q == *eq) return 0; // Empty token case
    return 'a'; // Assume it's always an argument for simplicity
}

t_cmd *parseredirs(t_cmd *ret, char **ps, char *es) {
    // Mock implementation of parseredirs
    // For now, we'll just return the same command pointer
    return ret;
}

char *ft_substring(char *q, char *eq) {
    size_t len = eq - q;
    char *substr = malloc(len + 1);
    strncpy(substr, q, len);
    substr[len] = '\0';
    return substr;
}

void ft_append_argv(char **argv, char *arg) {
    // A simple function to append the argument to argv
    while (*argv)
        argv++;
    *argv = arg;
}



void	handle_tokens(t_cmd *cmd, t_cmd **ret, char **ps, char *es)
{
	int		tok;
	int		argc;
	char	*q;
	char	*eq;
	char	*s;

	argc = 0;
	// init_cmd_args(cmd);
	while (!peek(ps, es, "|)&;"))
	{
		tok = gettoken(ps, es, &q, &eq);
		if (tok == 0)
			break ;
		if (tok != 'a')
			panic("syntax");
		s = ft_substring(q, eq);
		ft_append_argv(cmd->argv, s);
		// add_argument(cmd, q, eq, &argc);
		*ret = parseredirs(*ret, ps, es);
	}
}

// Test function
void test_handle_tokens() {
    t_cmd cmd;
    memset(&cmd, 0, sizeof(t_cmd)); // Initialize cmd to zero

    t_cmd *ret = &cmd;
    char input[] = "echo hello world |"; // Input string with tokens
    char *ps = input;
    char *es = input + strlen(input);

    handle_tokens(&cmd, &ret, &ps, es);

    // Assert that arguments were parsed and added to argv
    assert(strcmp(cmd.argv[0], "echo") == 0);
    assert(strcmp(cmd.argv[1], "hello") == 0);
    assert(strcmp(cmd.argv[2], "world") == 0);
    assert(cmd.argv[3] == NULL); // Ensure no more arguments

    printf("Test passed!\n");
}

int main() {
    test_handle_tokens();
    return 0;
}
