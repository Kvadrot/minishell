/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:50:28 by ufo               #+#    #+#             */
/*   Updated: 2024/11/26 17:24:47 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_env_var_substitution(t_data **minishell, char **full_arg,
		char *arg_duplicate, int start_index)
{
	t_env	*temp_env;
	char	*insertable_str;
	int		insertable_str_len;
	char	*result_arg;

	temp_env = (*minishell)->env;
	while (temp_env)
	{
		if (ft_strcmp(temp_env->key, arg_duplicate + 1) == 0)
		{
			insertable_str = temp_env->value;
			insertable_str_len = ft_strlen(insertable_str);
			result_arg = ft_insert_str(*full_arg, ft_get_arg_len(*full_arg
						+ start_index) + 1, insertable_str, start_index);
			free(*full_arg);
			*full_arg = result_arg;
			return (insertable_str_len);
		}
		temp_env = temp_env->next;
	}
	result_arg = ft_insert_str(*full_arg, ft_get_arg_len(*full_arg
				+ start_index) + 1, "", start_index);
	free(*full_arg);
	*full_arg = result_arg;
	return (0);
}

int	ft_substitude(t_data **minishell, char **full_arg, int start_index)
{
	char	*arg_duplicate;
	int		insertable_str_len;

	arg_duplicate = create_arg_duplicate(full_arg, start_index);
	if (!arg_duplicate)
		return (0);
	if (ft_strcmp(arg_duplicate, "$?") == 0)
		insertable_str_len = handle_exit_status_substitution(full_arg,
				start_index);
	else
		insertable_str_len = handle_env_var_substitution(minishell, full_arg,
				arg_duplicate, start_index);
	free(arg_duplicate);
	return (insertable_str_len);
}

/** TODO: ft_is_able_to_substitute
* @brief: Determines if a variable ($) in the argument can be substituted
*         based on its position in single or double quotes.
* @takes: full_arg - full argument string,
*         dollar_pointer - pointer to the dollar sign
//=======================================================================//
* @HOW_IT_WORKS:
1) Initialize super_quote to 'n' (no quote).
2) Iterate through full_arg until dollar_pointer.
*   - Track opening/closing single or double quotes.
3) Return true if no quotes or inside double quotes,
*    false if inside single quotes.
//=======================================================================//
* @returns: true - substitution allowed, false - not allowed
*/
bool	ft_is_able_to_substitude(char *full_arg, char *dollar_pointer)
{
	int		counter;
	char	super_quote;

	super_quote = 'n';
	counter = 0;
	if (!dollar_pointer || !*dollar_pointer
		|| ft_isprint(*(++dollar_pointer)) == 0 || *dollar_pointer == '\''
		|| *dollar_pointer == '\"')
		return (false);
	while (&full_arg[counter] != dollar_pointer)
	{
		if (full_arg[counter] == '\'' || full_arg[counter] == '\"')
		{
			if (super_quote == 'n')
				super_quote = full_arg[counter];
			else if (super_quote == full_arg[counter])
				super_quote = 'n';
		}
		counter++;
	}
	if (super_quote == '\"' || super_quote == 'n')
		return (true);
	else
		return (false);
}

/** TODO: ft_expand_arg
* @brief: unwraps given args (substitude env val instead $ARG)
* @takes: minishell->env, temp arg
//=======================================================================//
* @HOW_IT_works:
1) Looks for $ sign
2) iterates while char is alphabetical or numeric + underline
3) checks for opened quotes before and identify its type
4) checkes for super quotes(if it is ' then keep the string)
//=======================================================================//
* @returns: unwraped string
*/
char	*ft_expand_arg(t_data **minishell, char **temp_arg)
{
	int	counter;
	int	temp_arg_len;

	counter = 0;
	temp_arg_len = 0;
	while ((*temp_arg)[counter] != '\0')
	{
		if ((*temp_arg)[counter] == '$')
		{
			temp_arg_len = ft_get_arg_len(*temp_arg + counter);
			if (temp_arg_len > 0)
			{
				if (ft_is_able_to_substitude(*temp_arg,
						&(*temp_arg)[counter]) == true)
				{
					ft_substitude(minishell, temp_arg, counter);
				}
			}
		}
		counter++;
	}
	return (*temp_arg);
}

/** TODO: ft_expand
* @brief: unwraps $ARGUMENTS, clean up unnecessary quotes
* @takes: full data + parsed list of commands
//=======================================================================//
* @HOW_IT_works:
1) iterates through all cmd_list through all commands
2) iterates through each argumnet
3) expands argument
4) deletes unnecessary quotes
//=======================================================================//
* @returns: ???
*/
void	ft_expand_input(t_data **minishell)
{
	t_command_full	*temp_cmd;
	char			*temp_arg;
	int				arg_counter;

	arg_counter = 0;
	temp_cmd = (*minishell)->commands;
	if (temp_cmd->args != NULL)
		temp_arg = temp_cmd->args[arg_counter];
	else
		return ;
	while (temp_cmd)
	{
		arg_counter = 0;
		temp_arg = temp_cmd->args[arg_counter];
		while (temp_arg)
		{
			temp_cmd->args[arg_counter] = ft_expand_arg(minishell, &temp_arg);
			temp_cmd->args[arg_counter] = ft_errase_quote(minishell, &temp_arg);
			arg_counter++;
			temp_arg = temp_cmd->args[arg_counter];
		}
		temp_cmd = temp_cmd->next;
	}
}
