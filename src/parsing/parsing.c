/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:19:56 by ssuchane          #+#    #+#             */
/*   Updated: 2024/08/29 15:05:04 by ssuchane         ###   ########.fr       */
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

t_command	*init_command(void)
{
	t_command	*node;

	node = (t_command *)malloc(sizeof(t_command));
	if (!node)
		return (NULL);
	node->args = NULL;
	node->input_redirection = NULL;
	node->output_redirection = NULL;
	node->heredoc_delimiter = NULL;
	node->output_append = NULL;
	node->next = NULL;
	return (node);
}

void	add_word_to_command(t_command *command, char *word)
{
	char	**new_args;
	int		i;
	int		j;

	i = 0;
	if (command->args)
	{
		while (command->args[i])
			i++;
	}
	new_args = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_args)
		return ;
	j = -1;
	while (++j < i)
		new_args[j] = command->args[j];
	new_args[i] = ft_strdup(word);
	new_args[i + 1] = NULL;
	if (command->args)
		free(command->args);
	command->args = new_args;
}

void	finalize_command(t_command *command)
{
	if (!command)
		return ;
	// Perform any necessary finalization steps here, if needed.
	// For instance, you could validate the command structure, ensure that the
	// redirections are set correctly, or handle special cases.
	printf("Command:\n");
	for (int i = 0; command->args && command->args[i]; i++)
		printf("  arg[%d]: %s\n", i, command->args[i]);
	if (command->input_redirection)
		printf("  Input redirection: %s\n", command->input_redirection);
	if (command->output_redirection)
		printf("  Output redirection: %s\n", command->output_redirection);
	if (command->heredoc_delimiter)
		printf("  Heredoc delimiter: %s\n", command->heredoc_delimiter);
	if (command->output_append)
		printf("  Output append: %s\n", command->output_append);
}

// there might be issue with input where there are more than 1 redirector
// resulting in overwriting the previous redirectiors file name
void	parse_tokens(t_data *minishell)
{
	t_command	*current;

	current = init_command();
	while (minishell->tokens != NULL)
	{
		if (minishell->tokens->type == T_WORD)
			add_word_to_command(current, minishell->tokens->value);
		else if (minishell->tokens->type == T_LESS)
		{
			minishell->tokens = minishell->tokens->next;
			current->input_redirection = minishell->tokens->value;
		}
		else if (minishell->tokens->type == T_GREAT)
		{
			minishell->tokens = minishell->tokens->next;
			current->output_redirection = minishell->tokens->value;
		}
		else if (minishell->tokens->type == T_DLESS)
		{
			minishell->tokens = minishell->tokens->next;
			current->heredoc_delimiter = minishell->tokens->value;
		}
		else if (minishell->tokens->type == T_DGREAT)
		{
			minishell->tokens = minishell->tokens->next;
			current->output_append = minishell->tokens->value;
		}
		else if (minishell->tokens->type == T_PIPE)
		{
			finalize_command(current);
			current->next = init_command();
			current = current->next;
		}
		minishell->tokens = minishell->tokens->next;
	}
	finalize_command(current);
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