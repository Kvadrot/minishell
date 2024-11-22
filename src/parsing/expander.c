/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:50:28 by ufo               #+#    #+#             */
/*   Updated: 2024/11/22 18:55:39 by mbudkevi         ###   ########.fr       */
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
    if (string[len++] == '?')
        return (len);
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
1) Copies everything to the left from our insert_index if is able to do it
2) Counts the right side (_something)
*  right side = src (******_$ARG_something) - insert_ind(pointer on $) - old_part_len
3) Joins left whith insertable_part = result
4) Joins result with right_part
//=======================================================================//
* @returns: new string
*/
char *ft_insert_str(char *src, int old_part_len, char *insertable_str, int insert_ind)
{
    char *result;
    char *left_part;
    char *right_part;
    int right_part_len;

    left_part = NULL;
    right_part = NULL;

    // 1) Left part from the start to insert_index
    if (insert_ind > 0)
    {
        left_part = ft_strndup(src, insert_ind);
        if (!left_part)
            return (NULL);
    }

    // 2) Right part starts after the old part we are replacing
    right_part_len = ft_strlen(src) - insert_ind - old_part_len;
    right_part = ft_strndup(src + insert_ind + old_part_len, right_part_len);
    if (!right_part)
    {
        free(left_part); // Clean up before returning
        return (NULL);
    }

    // 3) Join left part with the insertable string
    result = ft_strjoin(left_part, insertable_str);
    if (!result)
    {
        free(left_part);
        free(right_part);
        return (NULL);
    }

    // 4) Join the result with the right part
    char *final_result = ft_strjoin(result, right_part);
    if (!final_result)
    {
        free(left_part);
        free(right_part);
        free(result);
        return (NULL);
    }

    // Clean up
    free(left_part);
    free(right_part);
    free(result);

    return (final_result);
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

    arg_duplicate = ft_strndup(*full_arg + start_index, ft_get_arg_len(*full_arg + start_index) + 1);
    if (!arg_duplicate)
        ft_handle_error(true, "Malloc_error, printed by ft_substitude", 433, minishell);
    // ft_printf("argduplicate = %s\n", arg_duplicate);

    if (ft_strcmp(arg_duplicate, "$?") == 0)
    {
        ft_printf("status = %d\n", g_last_exit_status);
        insertable_str = ft_itoa(g_last_exit_status);
        insertable_str_len = ft_strlen(insertable_str);
        *full_arg = ft_insert_str(*full_arg, ft_get_arg_len(*full_arg + start_index) + 1, insertable_str,  start_index);
        free(arg_duplicate);
        return insertable_str_len;
    }
    temp_env = (*minishell)->env;
    while (temp_env)
    {
        if (ft_strcmp(temp_env->key, arg_duplicate + 1) == 0)
        {
            insertable_str = temp_env->value;
            insertable_str_len = ft_strlen(insertable_str);
            *full_arg = ft_insert_str(*full_arg, ft_get_arg_len(*full_arg + start_index) + 1, insertable_str,  start_index);

            free(arg_duplicate);
            return insertable_str_len;
        }
        temp_env = temp_env->next;
    }
    ft_printf("*full_arg after substitution = %s\n", *full_arg);
    *full_arg = ft_insert_str(*full_arg, ft_get_arg_len(*full_arg + start_index) + 1, "",  start_index);
    free(arg_duplicate);
    return 0;
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
                    ft_printf("temp_arg after substitution = %s\n", *temp_arg);
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
2) iterates through each argumnet
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

    while (temp_cmd)
    {
        arg_counter = 0;
        temp_arg = temp_cmd->args[arg_counter];
        while (temp_arg)
        {
            temp_cmd->args[arg_counter] = ft_expand_arg(minishell, &temp_arg);
            temp_cmd->args[arg_counter] = ft_errase_quote(minishell, &temp_arg);
            ft_printf("ft_errase_quote result = %s\n", temp_cmd->args[arg_counter]);
            arg_counter++;
            temp_arg = temp_cmd->args[arg_counter];
        }
        temp_cmd = temp_cmd->next;
    }
}

