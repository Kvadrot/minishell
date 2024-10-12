/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbudkevi <mbudkevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:44:31 by mbudkevi          #+#    #+#             */
/*   Updated: 2024/10/12 20:38:22 by mbudkevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	delete_node(t_env **head_ref, t_env *node_to_delete)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *head_ref;
	prev = NULL;
	// Case 1: If the node to be deleted is the head node
	if (tmp != NULL && tmp == node_to_delete) {
		*head_ref = tmp->next; // Move the head to the next node
		free(tmp->key);  // Free the key
		free(tmp->value);  // Free the value
		free(tmp);  // Free the node itself
		return;
	}
	// Case 2: Search for the node in the rest of the list
	while (tmp != NULL && tmp != node_to_delete) {
		prev = tmp;
		tmp = tmp->next;
	}
	// If the node was not found
	if (tmp == NULL) {
		return;
	}
	// Unlink the node from the list
	prev->next = tmp->next;
	// Free the memory
	free(tmp->key);
	free(tmp->value);
	free(tmp);
}

void	add_to_env(t_data **minishell, char *key, char *new_value)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = (*minishell)->env;
	prev = NULL;
	//Check if the key exists and update if it does
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0)
			delete_node(&(*minishell)->env, tmp);
		tmp = tmp->next;
	}
	environment_new_node_end(*minishell, key, new_value);
}

int	builtin_cd(t_data **minishell)
{
	char	current_pwd[1024];
	char	new_pwd[1024];

	if (getcwd(current_pwd, sizeof(current_pwd)) == NULL)
	{
		ft_printf_full("error getting current directory", 2, NULL);
		return (1);
	}
	if ((*minishell)->commands->args[1])
	{
		ft_printf_full("too many arguments", 2, NULL);
		return (1);
	}
	if (chdir((*minishell)->commands->args[0]) == -1)
	{
		printf("command is: %s\n", (*minishell)->commands->args[0]);
		ft_printf_full("No such file or directory\n", 2, NULL);
		return (1);
	}
	add_to_env(minishell, "OLDPWD", current_pwd);
	if (getcwd(new_pwd, sizeof(new_pwd)) == NULL)
	{
		ft_printf_full("error getting new directory", 2, NULL);
		return (1);
	}
	add_to_env(minishell, "PWD", new_pwd);
	return (0);
}
