// #include "../../inc/minishell.h"

// t_command	*create_command(void)
// {
// 	t_command	*cmd;

// 	cmd = malloc(sizeof(t_command));
// 	if (!cmd)
// 		return (NULL);
// 	cmd->args = malloc(MAX_TOKENS * sizeof(char *));
// 	if (!cmd->args)
// 		return (NULL);
// 	cmd->input_file = NULL;
// 	cmd->output_file = NULL;
// 	cmd->append_file = NULL;
// 	cmd->heredoc_content = NULL;
// 	cmd->next = NULL;
// 	return (cmd);
// }

// void	add_argument(t_command *cmd, char *arg)
// {
// 	int	i;

// 	i = 0;
// 	while (cmd->args[i] != NULL)
// 		i++;
// 	cmd->args[i] = strdup(arg);
// 	cmd->args[i + 1] = NULL; // Keep args NULL-terminated for execve
// }

// t_command	*parse_tokens(t_tokens **tokens, int num_tokens)
// {
// 	t_command	*head;
// 	t_command	*current;
// 	t_tokens	*token;
// 	int			i;

// 	head = NULL;
// 	current = NULL;
// 	i = 0;
// 	while (i < num_tokens)
// 	{
// 		// load first token
// 		token = tokens[i];
// 		// in case the first token is of type T_WORD
// 		if (token->type == T_WORD)
// 		{
// 			if 


// 			// Start a new command if necessary
// 			if (current == NULL)
// 			{
// 				current = create_command();
// 				if (head == NULL)
// 				{
// 					head = current;
// 				}
// 			}
// 			// Add the token as an argument to the current command
// 			add_argument(current, token->value);
// 			break ;
// 		}

// 		case TOKEN_PIPE:
// 			// Prepare for the next command in the pipeline
// 			current->next = create_command();
// 			current = current->next;
// 			break ;

// 		case TOKEN_REDIRECT_OUT:
// 			// Set the output redirection file
// 			if (++i < num_tokens && tokens[i]->type == TOKEN_WORD)
// 			{
// 				current->output_file = strdup(tokens[i]->value);
// 			}
// 			break ;

// 		case TOKEN_APPEND_OUT:
// 			// Set the output append redirection file
// 			if (++i < num_tokens && tokens[i]->type == TOKEN_WORD)
// 			{
// 				current->append_file = strdup(tokens[i]->value);
// 			}
// 			break ;

// 		case TOKEN_REDIRECT_IN:
// 			// Set the input redirection file
// 			if (++i < num_tokens && tokens[i]->type == TOKEN_WORD)
// 			{
// 				current->input_file = strdup(tokens[i]->value);
// 			}
// 			break ;

// 		case TOKEN_HEREDOC:
// 			// Handle here document (<<)
// 			if (++i < num_tokens && tokens[i]->type == TOKEN_WORD)
// 			{
// 				char *delimiter = tokens[i]->value;
// 				size_t buffer_size = 1024;
// 				current->heredoc_content = malloc(buffer_size);
// 				current->heredoc_content[0] = '\0';

// 				char line[256];
// 				printf("heredoc> ");
// 				while (fgets(line, sizeof(line), stdin))
// 				{
// 					// Strip newline character from the input line
// 					line[strcspn(line, "\n")] = '\0';
// 					if (strcmp(line, delimiter) == 0)
// 					{
// 						break ; // End of heredoc
// 					}
// 					// Append the line to heredoc content
// 					strncat(current->heredoc_content, line, buffer_size
// 						- strlen(current->heredoc_content) - 1);
// 					strncat(current->heredoc_content, "\n", buffer_size
// 						- strlen(current->heredoc_content) - 1);
// 					printf("heredoc> ");
// 				}
// 			}
// 			break ;

// 		default:
// 			// Handle unexpected tokens (optional)
// 			fprintf(stderr, "Unexpected token: %s\n", token->value);
// 			break ;
// 		}
// 		i++;
// 	}

// 	return (head);
// }


// // case 1: token is a word
// if (token->type == T_WORD)
// {
// 	if ()
// }
