/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itykhono <itykhono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 21:24:45 by marvin            #+#    #+#             */
/*   Updated: 2024/08/27 14:51:15 by itykhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * environment_new_node_end()
 * 
 * @brief coppies givven param and initialize new node with copied parameters
 *
 * @param key Name of Key in env_list
 * @param value Value thats is assosiated with Key in env_list
 *
 * @return new environment node, type:  t_env *
 */
t_env	*environment_new_node(char *key, char *value)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	if (new_node->key == NULL || new_node->value == NULL)
		return (NULL);
	return (new_node);
}

/**
 * environment_new_node_end()
 * 
 * @brief Adds new environment node (key: value) to the end of environment_list
 *
 * @param head Pointer that contains entire list
 * @param key Name of Key in env_list
 * @param value Value thats is assosiated with Key in env_list
 *
 * @return status_code:
 * 200 everything is GOOD;
 * 400 and whatever else is BAD;
 */
int	environment_new_node_end(t_env **head, char *key, char *value)
{
	t_env	*new_node;
	t_env	*current;

	new_node = environment_new_node(key, value);
	if (!new_node)
		return (-400);
	if (*head == NULL)
		*head = new_node;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
	return (200);
}


/**
 * environment_new_node_end()
 * 
 * @brief takes sh_lvl, converts into int, increaments by 1, converts into char *
 *  SHLVL stands for Shell Level. So its should be increased each time you run any Shell.
 * 
 * @param current_val value that was copied from environment
 * 
 * @return incremented shell_level, type: char *
 */
static char	*ft_increment_shlvl(char *current_val)
{
	int		curr_val;
	char	*new_val;
	
	curr_val = ft_atoi(current_val);
	curr_val += 1;
	new_val = ft_itoa(curr_val);
	if (!new_val)
		return (NULL);
	return (new_val);
}

int	init_environment(t_env **environment, char **env)
{
	char	*key;
	char	*value;
	char	*delimiter_pos;
	int		i;
	int		result_status;

	result_status = 200;
	*environment = NULL;
	i = 0;
	while (env[i])
	{
		delimiter_pos = ft_strchr(env[i], '=');
		if (delimiter_pos != NULL)
		{
			key = ft_strndup(env[i], delimiter_pos - env[i]);
			if (!key)
			{
				environment_free_list(*environment);
				ft_printf("mem_error occured\n");
				return (-400);
			}
			value = ft_strdup(delimiter_pos + 1);
			if (!value)
			{
				free(key);
				environment_free_list(*environment);
				ft_printf("mem_error occured\n");
				return (-401);
			}

			if (ft_strncmp(key, "SHLVL", 5) == 0)
			{
				value = ft_increment_shlvl(value);
				if (!value)
				{
					free(key);
					environment_free_list(*environment);
					ft_printf("mem_error occured\n");
					return (-402);				
				}
			}
			environment_new_node_end(environment, key, value);
			// if (environment_new_node_end(environment, key, value) < 0);
			// {
			// 	free(key);
			// 	free(value);
			// 	ft_printf("mem_error occured 1\n");
			// 	environment_free_list(*environment);
			// 	return (-405);
			// }
			free(key);
			free(value);
		}
		i++;
	}
	return (200);
}

// function to free the list
void	environment_free_list(t_env *head)
{
	t_env	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

// tester function
void	print_environment(t_env *node)
{
	t_env	*current;

	current = node;
	while (current != NULL)
	{
		printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}