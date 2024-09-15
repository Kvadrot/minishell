

# include "./inc/minishell.h"

void	take_input(t_heredoc_cmd *cmd, char **ps, char *es)
{
	char	*s;
	int		ret;
	char	*q;
	char	*eq;
	char	*token;
	

	s = *ps;
	if (peek(ps, es, "<|>&;()"))
		panic("parse error near");
	gettoken(ps, es, &q, &eq);
	token = ft_strncpy(malloc(eq - q + 1), q, eq - q);
	
	while (ft_strncmp(token, q, ft_strlen(token)) != 0)
	{
		cmd->argv[0] = ft_strjoin(cmd->argv[0], readline("heredoc> "));
		cmd->argv[0] = ft_strjoin(cmd->argv[0], "\n");
	}
	ret = gettoken(ps, es, &q, &eq);
	readline(s);
}

int main(int argc, char *argv[])
{
    t_heredoc_cmd cmd;
    cmd.type = 0;
    cmd.argv = NULL;

    // Simulate taking input
    char *input = "example input";
    char *input_end = input + strlen(input);
    take_input(&cmd, &input, input_end);

    // Print argv contents
    if (cmd.argv != NULL) {
        for (int i = 0; cmd.argv[i] != NULL; i++) {
            printf("argv[%d]: %s\n", i, cmd.argv[i]);
        }
    } else {
        printf("argv is empty\n");
    }

    // Free allocated memory
    if (cmd.argv != NULL) {
        for (int i = 0; cmd.argv[i] != NULL; i++) {
            free(cmd.argv[i]);
        }
        free(cmd.argv);
    }

    return 0;
}