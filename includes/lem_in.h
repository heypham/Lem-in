/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 13:43:08 by epham             #+#    #+#             */
/*   Updated: 2019/10/10 17:46:35 by epham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>

# include <stdio.h>

#define TABLE_SIZE 10007

#define RED 	"\x1B[31m"
#define GRN 	"\x1B[32m"
#define YEL 	"\x1B[33m"
#define BLU 	"\x1B[34m"
#define MAG 	"\x1B[35m"
#define CYN 	"\x1B[36m"
#define WHT 	"\x1B[37m"
#define RESET 	"\x1B[0m"

/*
***		NEXT POUR HASH, PREV POUR BFS
*/

typedef	struct		s_room
{
	char			*name;
	int				coord_x;
	int				coord_y;
	int				visited;
	int				inpath;
	int				inqueue;
	int				prev_flow;
	int				weight;
	struct 	s_link	*linked_rooms;
	struct	s_link	*from;
	struct	s_room	*prev;
	struct	s_room	*next;      // separate chaining
}					t_room;

/*
***		FLOW MODIFIED BY EDMUND KARP ALGO
*/

typedef struct		s_link
{
	t_room			*dest;
	t_room			*from;
	int				flow;
	struct 	s_link	*rev;
	struct	s_link	*next;
}					t_link;

typedef struct 		s_solution
{
	struct	s_path	*path;
	int				ants;
	int				ants_sent;
	int				ants_arrived;
	int				pathlen;
	int				steps;
	struct	s_solution	*next;
}					t_solution;


typedef struct		s_path
{
	t_room			*room;
	int				ant_index;
	struct	s_path	*prev;
	struct	s_path	*next;
}					t_path;

typedef	struct 		s_queue
{
	t_room			*room;
	int				prev_flow;
	struct 	s_queue	*next;
}					t_queue;

typedef struct		s_line
{
	char			*line;
	struct	s_line	*next;
}					t_line;

typedef struct		s_env
{
	char			*line;
	int				ant_nb;
	int				next_ant;
	int				flag_link;
	int				path_nb;
	int				total_len;
	int				ants_sent;
	int				steps;
	t_line			*read;
	t_link			*links;
	t_room			**table;
	t_room			*start;
	t_room			*end;
	t_queue			*queue;
	t_queue			*end_queue;
	t_solution		*current_sol;
	t_solution		*optimal_sol;
	t_solution		*shortest_path;
	t_solution		*second_shortest;
}					t_env;

void				parse(t_env *env);

/*
***		print
*/

t_line				*create_line(char *content);
void				add_line(t_env *env, t_line	*line);
void				print_map(t_env *env);
void				get_line(t_env *env);

/*
***		hash
*/

unsigned long long	hash_value(char *key);
void				init_table(t_room **table);
void				insert_hash_table(t_room **table, t_room *room);
void				print_hash(t_room **table, size_t size);

/*
***		rooms
*/

t_room				*create_room(char *line);
void				add_room(t_env *env, t_room *room);
void				parse_startend(t_env *env, t_room **table);
t_room 				*find_room(t_room **table, char *room_name);

/*
***		links
*/

void 				add_link(t_room *room, t_link *link);
void				*get_link(t_env *env, t_room **table, char *line);
void				parse_links(t_env *env);

/*
***		checkers
*/

int					is_room(char *line);
int					is_command(char *line);
int					is_comment(char *line);
int					is_link(char *line);
int					command_type(char *line);

/*
***		BFS
*/

int  				bfs(t_env *env);
int					edmond(t_env *env);
void				print_sol(t_env *env, t_solution *solution);

/*
***		QUEUE
*/

void				append_queue(t_env *env, t_link *link, t_room *prev);
void				insert_after_queue(t_env *env, t_link *link, t_room *prev);
void				insert_before_queue(t_env *env, t_link *link, t_room *prev);

/*
***		OPTI BFS
*/

int					check_change_source(t_env *env, t_room *room, t_room *new);
void				change_source(t_env *e, t_room *r, t_link *l, t_room *new);
int					remontada(t_env *env, t_room *curr, t_link *curr_link);
void				depthfirst_queue(t_env *env, t_room *room);

/*
***		PATHS
*/

t_path				*create_pathlink(t_env *env, t_room *room);
t_path				*get_path(t_env *env, t_room *next, t_solution *sol);
int					remove_path(t_env *env, t_solution *sol);
int					check_steps(t_env *env);
void				free_path(t_path *path);

/*
***		SOLUTIONS
*/

t_solution			*create_solution(t_env *env, t_room *next);
void				append_sol(t_env *env, t_solution *new);
t_solution			*dispatch_ants(t_env *env, t_solution *head);
void				free_sol(t_solution *sol);

/*
***		utils
*/

void				ft_error(int error);
void				print_paths(t_solution *current_sol);
void				print_path(t_path *head);
void				print_queue(t_env *env);
void				printqueue(t_queue *queue);
void				print_links(t_room *room);
void				print_link(t_link *link);
void				free_table(t_room **table);
void 				free_links(t_link *links);
void 				free_rooms(t_room *rooms);
void 				free_lines(t_line *line);
void 				free_2darray(char **arr);

	void print_bfs(t_env *env);

#endif