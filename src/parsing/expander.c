/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:50:28 by ufo               #+#    #+#             */
/*   Updated: 2024/10/19 17:04:16 by ufo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


/** TODO: ft_get_arg_len
* @brief: counts len of given $ARG ($ + amount of signs after it)
* @takes: char * = $ start pointer of our ->$<- ARG
//=======================================================================//
* @HOW_IT_works:
1) iterates while char is alphabetical or numeric + underline
//=======================================================================//
* @returns: (length - $) exmp: $ARG = 3
*/
int ft_get_arg_len(char *string)
{
    int len;

    len = 0;
    string++;
    while (string[len] != '\0' && (ft_isdigit(string[len]) || ft_isalpha(string[len]) || string[len] == '_'))
        len++;
    return (len);
}

/** TODO: ft_insert_str
* @brief: inserts strings into dest string according to insert start_index
* @takes: dest - string where to insert,
          int old_part_len lengt of part we are going to crop
          insertable_str - string to insert,
          insert_ind
//=======================================================================//
* @HOW_IT_WORKS:

//=======================================================================//
* @returns: new string
*/
char *ft_insert_str(char *src, int old_part_len,  char *insertable_str, int insert_ind)
{
    char    *result;
    char    *left_part;
    char    *right_part;

    if (insert_ind > 0)
    {
        left_part = ft_strndup(src, insert_ind);
        if (!left_part)
           return (NULL); 
    }
    right_part = ft_strndup(src, insert_ind + old_part_len);
    if (!right_part)
        return (NULL);
    result = ft_strjoin(left_part, insertable_str);
    if (!result)
        return (NULL);
    result = ft_strjoin(result, right_part);
    ft_printf("inserting result = %s\n", result);
    return (result);
}

/** TODO: ft_substitude
* @brief: substitudes values from environment instead of $ARG
* @takes: minishell, source, index - start of substitution
//=======================================================================//
* @HOW_IT_WORKS:
1) Creates duplicate of our $arg
2) iterates through the env list of minishell comparing the keys
3)
* if key matches to the $arg
*  inserts its value instead of $arg
* else if there is no matche
*   cuts out $arg from our full_arg and
//=======================================================================//
* @returns: length of substituted string / or 0 in no match case
*/
int ft_substitude(t_data **minishell, char **full_arg, int start_index)
{
    char *insertable_str;
    t_env *temp_env;
    char *arg_duplicate;
    int insertable_str_len;

    // 1) Duplicate the argument after the '$'
    arg_duplicate = ft_strndup(*full_arg + start_index + 1, ft_get_arg_len(*full_arg + start_index));
    if (!arg_duplicate)
        ft_handle_error(true, "Malloc_error, printed by ft_substitute", 433, *minishell);
    ft_printf("argduplicate = %s\n", arg_duplicate);
    // 2) Iterate through the environment list
    temp_env = (*minishell)->env;
    while (temp_env)
    {
        // 3) Compare the environment key with the duplicated argument
        
        if (ft_strcmp(temp_env->key, arg_duplicate) == 0)
        {
            // 4) If key matches, insert its value into full_arg
            insertable_str = temp_env->value;
            insertable_str_len = ft_strlen(insertable_str);

            // Assuming ft_insert_str modifies full_arg correctly
            *full_arg = ft_insert_str(*full_arg, ft_get_arg_len(*full_arg + start_index), insertable_str,  start_index);

            free(arg_duplicate);  // Clean up
            return insertable_str_len;  // Return the length of the substituted string
        }
        ft_printf("temp_env = %s\n", temp_env->key);
        temp_env = temp_env->next;  // Move to the next environment variable
    }
    ft_printf("*full_arg after substitution = %s\n", *full_arg);

    // 5) If no match is found, remove the $ARG from full_arg
    // *full_arg = ft_remove_str(*full_arg, start_index, ft_get_arg_len(*full_arg + start_index));

    free(arg_duplicate);  // Clean up
    return 0;  // No substitution occurred
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
bool ft_is_able_to_substitude(char *full_arg, char *dollar_pointer)
{
    int counter;
    char super_quote;

    super_quote = 'n';
    counter = 0;
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
char *ft_expand_arg(t_data **minishell, char **temp_arg)
{
    char super_quote; // " somethingkagjjg jwog;erogh 'test'  " super quote is ""
    int counter;
    int temp_arg_len;
    int substituted_str_len;

    counter = 0;
    temp_arg_len = 0;

    ft_printf("ft_expand_arg starts with %s\n", *temp_arg);
    
    while ((*temp_arg)[counter] != '\0') // Proper dereferencing
    {
        if ((*temp_arg)[counter] == '$') // Proper dereferencing
        {
            temp_arg_len = ft_get_arg_len(*temp_arg + counter);
            if (temp_arg_len > 0)
            {
                if (ft_is_able_to_substitude(*temp_arg, &(*temp_arg)[counter]) == true) // Pass pointer to the character
                {
                    substituted_str_len = ft_substitude(minishell, temp_arg, counter);
                    ft_printf("temp_arg after substitution = %s\n", *temp_arg); // Dereference to print the string
                    ft_printf("some at least it compiles\n");
                }
            }
        }
        counter++;
    }

    return *temp_arg; // Return the modified argument
}

/** TODO: ft_expand
* @brief: unwraps $ARGUMENTS, clean up unnecessary quotes
* @takes: full data + parsed list of commands
//=======================================================================//
* @HOW_IT_works:
1) iterates through all cmd_list through all commands
2) iterates through all argumnets
3) expands argument
4) deletes unnecessary quotes
//=======================================================================//
* @returns: ???
*/
void ft_expand_input(t_data **minishell)
{
    t_command_full *temp_cmd;
    char *temp_arg;
    int arg_counter;

    arg_counter = 0;
    temp_cmd = (*minishell)->commands;
    if (temp_cmd->args != NULL)
        temp_arg = temp_cmd->args[arg_counter];
    else
        return;
    ft_printf("temp_arg_ft_expand_inputlen\n");

    while (temp_cmd)
    {
        while (temp_arg)
        {
            ft_expand_arg(minishell, &temp_arg);
            // TODO:
            //  ft_unwrap_quoetes();
            arg_counter++;
            temp_arg = temp_cmd->args[arg_counter];
        }
        temp_cmd = temp_cmd->next;
    }
    ft_printf("expander\n");
}