/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsirpa-g <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:39:19 by lsirpa-g          #+#    #+#             */
/*   Updated: 2025/09/02 12:39:20 by lsirpa-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

t_node	*create_node(int *valid_args, int args_len, t_table *table)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->id = 0;
	new_node->last_meal_time = 0;
	new_node->time_to_die = valid_args[1];
	new_node->time_to_eat = valid_args[2];
	new_node->time_to_sleep = valid_args[3];
	if (args_len == 5)
		new_node->times_to_eat = valid_args[4];
	else
		new_node->times_to_eat = -1;
	new_node->table = table;
	new_node->next = new_node;
	if (pthread_mutex_init(&new_node->fork_mutex, NULL) != 0)
		return (NULL);
	return (new_node);
}

int	add_node_back(t_node *head, t_node *new_node)
{
	t_node	*tmp;
	int		i;

	if (!new_node || !head)
		return (0);
	i = 1;
	tmp = head;
	while (tmp->next != head)
	{
		tmp = tmp->next;
		i++;
	}
	tmp->next = new_node;
	new_node->next = head;
	new_node->id = tmp->id + 1;
	return (1);
}

void	clear_list(t_node **head)
{
	t_node	*current;
	t_node	*next;

	if (*head == NULL)
		return ;
	if ((*head)->next == *head)
	{
		pthread_mutex_destroy(&(*head)->fork_mutex);
		free(*head);
		*head = NULL;
		return ;
	}
	current = (*head)->next;
	while (next != *head)
	{
		next = current->next;
		pthread_mutex_destroy(&current->fork_mutex);
		free(current);
		current = next;
	}
	pthread_mutex_destroy(&(*head)->fork_mutex);
	free(*head);
	*head = NULL;
}

t_node	*create_table(int count, int *valid_args, int args_len, t_table *table)
{
	t_node	*head;

	if (count <= 0)
		return (NULL);
	head = create_node(valid_args, args_len, table);
	if (!head)
		return (NULL);
	count--;
	while (count--)
	{
		if (!add_node_back(head, create_node(valid_args, args_len, table)))
			return (clear_list(&head), NULL);
	}
	return (head);
}
