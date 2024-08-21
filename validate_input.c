/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssuchane <ssuchane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:56:43 by ssuchane          #+#    #+#             */
/*   Updated: 2024/08/20 19:44:33 by ssuchane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Everything here is about testing the input for the minishell

void	validate_input(char **av)
{
	int	single_quote_flag;
	int	double_quite_flag;

	single_quote_flag = 0;
	double_quite_flag = 0;
	// Check for PIPE in the beginning of the input 
	// IF av[1][0] == '|'
		// output error 

	// Check for unclosed single or double quotes
	// IF av[1][0] == "'"
		// single_quote_flag++;
	// IF av[1][0] == """
		// double_quote_flag++;
	// IF av[last_argument][last_element] == "'"
		// single_quote_flag++;
	// IF av[last_argument][last_element] == """
		// double_quote_flag++;
	// IF single_quote_flag OR double_quote_flag != 0 OR != 2
		// output error
}

int	main(int ac, char **av)
{
	char	*input;

	input = "echo 'testing'";
	printf("%s\n", input);
	return (0);
}