/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoribeir <yoribeir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 20:26:13 by anonymous         #+#    #+#             */
/*   Updated: 2019/08/05 17:27:20 by yoribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	parse_ants(t_env *env)
{
	if (get_next_line(0, &env->line) < 1)
	{
		add_line(env, create_line(env->line));
		ft_error(1);
	}
	while (is_comment(env->line))
		get_line(env);
	if (!ft_isdigit(*env->line))
		ft_error(3);
	env->ant_nb = ft_atoi(env->line);
	if (env->ant_nb <= 0)
		ft_error(3);
	ft_strdel(&env->line);
}

void	reader(t_env *env, t_room **table)
{
	t_room	*room;

	while (get_next_line(0, &env->line) == 1)
	{
		add_line(env, create_line(env->line));
		if (is_room(env->line))
		{
			room = create_room(env->line);
			insert_hash_table(table, room);
		}
		if (is_link(env->line))
			if (!(get_link(env, table, env->line)))
				break ;
		if (is_command(env->line))
			parse_startend(env, table);
		if (!is_room(env->line) && !is_link(env->line) && !is_comment(env->line)
				&& !is_command(env->line))
		{
			printf("BREAK\n");
			break ;
		}
		ft_strdel(&env->line);
	}
}

void	parse(t_env *env)
{
	t_room	*table[TABLE_SIZE];

	init_table(table);
	parse_ants(env);
	printf("%d\n", env->ant_nb);
	reader(env, table);
	if (!env->start || !env->end)
		ft_error(4);
	if (!env->flag_link)
		ft_error(1);
}
