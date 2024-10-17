/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:50:28 by ufo               #+#    #+#             */
/*   Updated: 2024/10/17 16:55:34 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
/** TODO: ft_check_is_able_to_substitude
* @brief: checks wether super quetes are not single quotes''
* @takes: string - temp argument
//=======================================================================//
* @HOW_IT_works:
1) checks for opened quotes before and identify its type
//=======================================================================//
* @returns: Bool
*/
bool ft_check_is_able_to_substitude(char *str_argument)
{
	// if 
	return (true);
}

/** TODO: ft_might_be_substituted
* @brief: decides should we change unwrap the $ARG or not
* @takes: full args_arr, temp arg
//=======================================================================//
* @HOW_IT_works:
1) Looks for $ sign 
2) checks for opened quotes before and identify its type
//=======================================================================//
* @returns: Bool
*/
bool ft_might_be_substituted(char **super_arr, char *temp_arg)
{
	char	super_quote; // " somethingkagjjg jwog;erogh 'test'  " super quote is ""
	char	temp_pointer;
	bool	is_able_to_substitude;

	temp_pointer = temp_arg;
    while (ft_strchr(temp_pointer, '$'))
	{
		is_able_to_substitude = ft_check_is_able_to_substitude(temp_pointer);
		temp_pointer = ft_strchr(temp_pointer, '$');
		
		
		// temp_pointer = 
	}

    return (false);
}

/** TODO: ft_expand
* @brief: unwraps $ARGUMENTS, clean up unnecessary quotes 
* @takes: full data + parsed list of commands
//=======================================================================//
* @HOW_IT_works:
1) Looks for $ sign 
2) checks for opened quotes before and identify its type
3) substitude values from env indtead of $ARGS if neccessary
//=======================================================================//
* @returns: ???
*/
void	ft_expand_input(t_data **minishell, t_command_full **cmd)
{
    // t_command_full  *temp_cmd;
    // char            *temp_arg;
    // int             arg_counter;

    // temp_cmd =  *cmd;
    // arg_counter = 0;
    // temp_arg = temp_cmd->args[arg_counter];
    // while (temp_cmd)
    // {
    //     while (temp_arg)
    //     {
    //         if (ft_might_be_substituted(temp_cmd->args, temp_arg) == true)
    //         {
    //            // ft_substitude_env_val();
    //         }
    //         arg_counter++;
    //         temp_arg = temp_cmd->args[arg_counter];
    //     }
    //     temp_cmd = temp_cmd->next;
    // }
    ft_printf("expander\n");
}