/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epham <epham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 13:43:08 by epham             #+#    #+#             */
/*   Updated: 2019/07/11 11:32:06 by epham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>



# include <stdio.h>


typedef	struct	s_room
{
	char		*name;
	int			coord_x;
	int			coord_y;
}				t_room;

typedef struct	s_env
{
	char		*input;
	int			ant_nb;
	t_room		*start;
	t_room		*end;
}				t_env;

/*
***		INITIALIZE
*/

t_env			*initialize_env(t_env **env);

/*
***		PARSER
*/

void			get_input(t_env *env);
int				check_input(t_env *env);

/*
***		CHECK ERRORS
*/

int				check_ants(t_env *env, char **value);
int				get_start_end(t_env *env, char **args, char *startend);

#endif
