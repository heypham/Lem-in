/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anradixt <anradix@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 13:10:46 by anonymous         #+#    #+#             */
/*   Updated: 2019/08/04 19:36:42 by anradixt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	print_link(t_link *link)
{
	printf("\ndest : %s\n", link->dest->name);
	printf("flow : %d\n", link->flow);
	printf("from : %s\n\n", link->rev->dest->name);
}

void	print_links(t_room *room)
{
	t_link *head;

	head = room->linked_rooms;
	// printf("room %s is connected to : ", room->name);
	while (head)
	{
		if (head->next)
			printf("room %s, ", head->dest->name);
		else
			printf("room %s", head->dest->name);
		head = head->next;
	}
}

void	print_split(char **tab)
{
	int		i = 0;
	int		y = 0;

	while (tab[i])
	{
		while (tab[i][y])
		{
			printf("%c", tab[i][y]);
			y++;
		}
		printf(" ");
		y = 0;
		i++;
	}
	i = 0;
}

void	print_hash(t_room **table, size_t size)
{
	t_room	*collisions;
	size_t i;
	int	count = 0;

	i = 0;
	while (i < size)
	{
		if (table[i]->name)
		{
			// printf("hash %s", table[i]->name);
			print_links(table[i]);
			collisions = table[i];
			while (collisions->next)
			{
				count++;
				collisions = collisions->next;
				printf(" -> %s", collisions->name);
			}
			count++;
		}
		if (table[i]->name)
			printf("\n");
		i++;
	}
	printf("room number %d\n", count);
}

void	print_paths(t_solution *current_sol)
{
	t_solution	*head;
	t_path		*start;

	head = current_sol;
	while (current_sol)
	{
		printf("ANTS TO SEND IN THIS PATH : %d\n", current_sol->ants);
		start = current_sol->path;
		while (current_sol->path)
		{
			printf("%s | ", current_sol->path->room->name);
			current_sol->path = current_sol->path->next;
		}
		current_sol->path = start;
		printf("\n");
		current_sol = current_sol->next;
	}
	current_sol = head;
}

void	print_queue(t_env *env)
{
	t_queue *queue;

	if (env->queue)
	{
		queue = env->queue;
		printf("\nQUEUE : ");
		while (queue->next)
		{
			printf("room %s || ", queue->room->name);
			queue = queue->next;
		}
		printf("room %s\n\n", queue->room->name);
	}
}

void	free_table(t_room **table)
{
	int i;

	i = 0;
	while (i < TABLE_SIZE)
	{
		free(table[i]);
		i++;
	}
}

void	ft_error(int error)
{
	if (error == 1)
		ft_putstr_fd("ERROR\n", 2);
	if (error == 2)
		ft_putstr_fd("LINK TO UNKNOWN ROOM\n", 2);
	if (error == 3)
		ft_putstr_fd("INVALID ANTS\n", 2);
	if (error == 4)
		ft_putstr_fd("ROOM START OR END MISSING\n", 2);
	exit(1);
}