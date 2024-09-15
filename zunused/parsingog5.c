/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:19:56 by ssuchane          #+#    #+#             */
/*   Updated: 2024/08/31 20:27:08 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_syntax(t_tokens *tokens)
{
	t_tokens	*current;
	t_tokens	*previous;

	current = tokens;
	previous = NULL;
	while (current)
	{
		if (current->type == T_PIPE)
		{
			if (!previous || previous->type == T_PIPE)
			{
				printf("minishell: syntax error near unexpected token `%s'\n",
					current->value);
				return (0);
			}
		}
		else if (current->type == T_GREAT || current->type == T_DGREAT
			|| current->type == T_LESS || current->type == T_DLESS)
		{
			if (!current->next || current->next->type == T_PIPE)
			{
				if (current->next)
					printf("minishell: syntax error near unexpected token `newline'\n");
				else
					printf("minishell: syntax error near unexpected token `newline'\n");
				return (0);
			}
		}
		previous = current;
		current = current->next;
	}
	if (previous && (previous->type == T_PIPE || previous->type == T_GREAT
			|| previous->type == T_DGREAT || previous->type == T_LESS
			|| previous->type == T_DLESS))
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (0);
	}
	return (1);
}

t_command	*create_new_command(t_command *previous)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	cmd->args = NULL;
	cmd->input_redirection = NULL;
	cmd->output_redirection = NULL;
	cmd->heredoc_delimiter = NULL;
	cmd->output_append = NULL;
	cmd->pipe = 0;
	cmd->next = NULL;
	cmd->prev = previous;
	return (cmd);
}

void add_argument(t_command *cmd, const char *arg)
{
    int count = 0;

    // Count existing arguments
    if (cmd->args)
    {
        while (cmd->args[count])
        {
            count++;
        }
    }

    // Allocate space for the new argument and NULL terminator
    cmd->args = realloc(cmd->args, (count + 2) * sizeof(char *));
    if (!cmd->args)
    {
        perror("realloc");
        exit(EXIT_FAILURE);
    }
    
    // Add the new argument
    cmd->args[count] = strdup(arg);
    if (!cmd->args[count])
    {
        perror("strdup");
        exit(EXIT_FAILURE);
    }
    // We do not add NULL here; it's handled in parse_word_tokens
}

void	set_redirection(t_command *cmd, t_token_type type, const char *value)
{
	if (type == T_GREAT)
	{
		cmd->output_redirection = strdup(value);
	}
	else if (type == T_DGREAT)
	{
		cmd->output_append = strdup(value);
	}
	else if (type == T_LESS)
	{
		cmd->input_redirection = strdup(value);
	}
	else if (type == T_DLESS)
	{
		cmd->heredoc_delimiter = strdup(value);
	}
}

void parse_word_tokens(t_command *cmd, t_tokens **tokens)
{
    // Initialize args array
    cmd->args = NULL;

    // Add arguments while encountering T_WORD tokens
    while (*tokens && (*tokens)->type == T_WORD)
    {
        add_argument(cmd, (*tokens)->value);
        *tokens = (*tokens)->next;
    }

    // Null-terminate the args array
    if (cmd->args)
    {
        int count = 0;
        while (cmd->args[count])
        {
            count++;
        }
        cmd->args = realloc(cmd->args, (count + 1) * sizeof(char *));
        if (!cmd->args)
        {
            perror("realloc");
            exit(EXIT_FAILURE);
        }
        cmd->args[count] = NULL; // Ensure the array is NULL-terminated
    }
}

		}
	}
}

void	parse_pipe_token(t_command **previous, t_tokens **tokens)
{
	if (*tokens && (*tokens)->type == T_PIPE)
	{
		if (*previous)
		{
			(*previous)->pipe = 1;
		}
		*tokens = (*tokens)->next;
	}
}

void	print_commands(t_command *cmd)
{
	while (cmd)
	{
		printf("Command:\n");
		if (cmd->args)
		{
			printf("  Args: ");
			for (int i = 0; cmd->args && cmd->args[i]; i++)
			{
				printf("%s ", cmd->args[i]);
			}
			printf("\n");
		}
		if (cmd->input_redirection)
			printf("  Input Redirection: %s\n", cmd->input_redirection);
		if (cmd->output_redirection)
			printf("  Output Redirection: %s\n", cmd->output_redirection);
		if (cmd->output_append)
			printf("  Output Append: %s\n", cmd->output_append);
		if (cmd->heredoc_delimiter)
			printf("  Heredoc Delimiter: %s\n", cmd->heredoc_delimiter);
		printf("  Pipe: %d\n", cmd->pipe);
		cmd = cmd->next;
	}
}

t_command	*parse_tokens(t_tokens *tokens)
{
	t_command	*head;
	t_command	*current;
	t_command	*previous;

	head = NULL;
	current = NULL;
	previous = NULL;
	while (tokens)
	{
		current = create_new_command(previous);
		if (!head)
		{
			head = current;
		}
		parse_word_tokens(current, &tokens);
		parse_redirection_tokens(current, &tokens);
		parse_pipe_token(&previous, &tokens);
		if (previous)
		{
			previous->next = current;
		}
		previous = current;
	}
	print_commands(head);
	return (head);
}

void	free_commands(t_command *cmd)
{
	t_command	*temp;

	while (cmd)
	{
		temp = cmd;
		cmd = cmd->next;
		if (temp->args)
		{
			for (int i = 0; temp->args[i]; i++)
			{
				free(temp->args[i]);
			}
			free(temp->args);
		}
		free(temp->input_redirection);
		free(temp->output_redirection);
		free(temp->output_append);
		free(temp->heredoc_delimiter);
		free(temp);
	}
}

/*
void	execute_command_tree(t_command_node *root) {
	int pipe_fd[2];
	int input_fd = STDIN_FILENO;

	while (root) {
		if (root->next) {
			pipe(pipe_fd);
		}

		pid_t pid = fork();
		if (pid == 0) { // Child process
			if (root->input_redirection) {
				int fd = open(root->input_redirection, O_RDONLY);
				dup2(fd, STDIN_FILENO);
				close(fd);
			}

			if (root->output_redirection) {
				int fd = open(root->output_redirection,
		O_WRONLY | O_CREAT | O_TRUNC, 0644);
				dup2(fd, STDOUT_FILENO);
				close(fd);
			} else if (root->next) {
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[1]);
			}

			if (input_fd != STDIN_FILENO) {
				dup2(input_fd, STDIN_FILENO);
				close(input_fd);
			}

			execvp(root->args[0], root->args);
			// Handle execvp error
			exit(1);
		} else {
			if (input_fd != STDIN_FILENO) {
				close(input_fd);
			}
			if (root->next) {
				close(pipe_fd[1]);
				input_fd = pipe_fd[0];
			}
			root = root->next;
		}
	}
	while (wait(NULL) > 0); // Wait for all child processes
}

t_command	*create_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = malloc(MAX_TOKENS * sizeof(char *));
	if (!cmd->args)
		return (NULL);
	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->append_file = NULL;
	cmd->heredoc_content = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	add_argument(t_command *cmd, char *arg)
{
	int	i;

	i = 0;
	while (cmd->args[i] != NULL)
		i++;
	cmd->args[i] = strdup(arg);
	cmd->args[i + 1] = NULL; // Keep args NULL-terminated for execve
}

t_command	*parse_tokens(t_tokens **tokens, int num_tokens)
{
	t_command	*head;
	t_command	*current;
	t_tokens	*token;
	int			i;
	char		*delimiter;
	size_t		buffer_size;
			char line[256];

	head = NULL;
	current = NULL;
	i = 0;
	while (i < num_tokens)
	{
		// load first token
		token = tokens[i];
		// in case the first token is of type T_WORD
		if (token->type == T_WORD)
		{
			if
				// Start a new command if necessary
				if (current == NULL)
				{
					current = create_command();
					if (head == NULL)
					{
						head = current;
					}
				}
			// Add the token as an argument to the current command
			add_argument(current, token->value);
			break ;
		}
	case TOKEN_PIPE:
		// Prepare for the next command in the pipeline
		current->next = create_command();
		current = current->next;
		break ;
	case TOKEN_REDIRECT_OUT:
		// Set the output redirection file
		if (++i < num_tokens && tokens[i]->type == TOKEN_WORD)
		{
			current->output_file = strdup(tokens[i]->value);
		}
		break ;
	case TOKEN_APPEND_OUT:
		// Set the output append redirection file
		if (++i < num_tokens && tokens[i]->type == TOKEN_WORD)
		{
			current->append_file = strdup(tokens[i]->value);
		}
		break ;
	case TOKEN_REDIRECT_IN:
		// Set the input redirection file
		if (++i < num_tokens && tokens[i]->type == TOKEN_WORD)
		{
			current->input_file = strdup(tokens[i]->value);
		}
		break ;
	case TOKEN_HEREDOC:
		// Handle here document (<<)
		if (++i < num_tokens && tokens[i]->type == TOKEN_WORD)
		{
			delimiter = tokens[i]->value;
			buffer_size = 1024;
			current->heredoc_content = malloc(buffer_size);
			current->heredoc_content[0] = '\0';
			printf("heredoc> ");
			while (fgets(line, sizeof(line), stdin))
			{
				// Strip newline character from the input line
				line[strcspn(line, "\n")] = '\0';
				if (strcmp(line, delimiter) == 0)
				{
					break ; // End of heredoc
				}
				// Append the line to heredoc content
				strncat(current->heredoc_content, line, buffer_size
					- strlen(current->heredoc_content) - 1);
				strncat(current->heredoc_content, "\n", buffer_size
					- strlen(current->heredoc_content) - 1);
				printf("heredoc> ");
			}
		}
		break ;
	default:
		// Handle unexpected tokens (optional)
		fprintf(stderr, "Unexpected token: %s\n", token->value);
		break ;
	}
	i++;
}

return (head);
}

// case 1: token is a word
if (token->type == T_WORD)
{
	// if next token is T_WORD
	if ()
	{
		// create command
		// all next consequtive T_WORD tokens will be arguments
		// outside of this if/function we will have to update token to move past
		// all used T_WORD type of tokens
	}
	// if next token is T_PIPE |
	else if ()
	{
		// change standard_output to standard_input
	}
	// if next word is T_LESS <
	else if ()
	{
		// check if the file exists and we have read rights to it --access-- functon
	}
	// if next word is T_DLESS <<
	else if ()
	{
		// we are dealing with here_doc
	}
	// if next word is T_GREAT >
	else if ()
	{
		// we are dealing with command for sure
	}
	// if next word is T_DGREAT >>
	else if ()
	{
		// we are dealing with command for sure
	}
}

// case 2: token is >
if (token->type == T_GREAT)
{
	// check if next token is T_WORD
	if (true)
	{
		// check whether we can create a file of that name,
			if there is enough space
		// on disk to do it, create the file with read/write properties
	}
	else
	// error
}

// case 3: token is >>
if (token->type == T_DGREAT)
{
	// check if next token is T_WORD
	if (true)
	{
		// check whether the file of that name exists,
			whether we have rights to read/write
		// to that file
		// append output from what was before to the end of the file
	}
	else
	// error
}

// case 4: token is |
if (token->type == T_PIPE)
{
	// check whether the next token type is T_WORD
	if (true)
	{
		// feed the output from previous command to the input of new command
	}
	else
	// error
}



*/