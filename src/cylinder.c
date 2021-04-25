/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 14:50:58 by lseema            #+#    #+#             */
/*   Updated: 2021/04/25 00:23:54 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "token_actions.h"

void		parse_cylinder(char const *json, jsmntok_t **tkn, t_scene **scene,
	int size)
{
	t_object		*object;
	t_cylinder_data	*cylinder_data;

	cylinder_data = (t_cylinder_data *)malloc(sizeof(t_cylinder_data));
	object = new_object(cylinder_data, OBJ_CYLINDER);
	object->data = cylinder_data;
	while (--size)
	{
		if (json_eq(json, **tkn, "coordinates"))
		{
			++(*tkn);
			object->origin = token_to_vec3(json, tkn);
		}
		else if (json_eq(json, **tkn, "color"))
		{
			++(*tkn);
			object->color = token_to_color(json, tkn);
		}
		else if (json_eq(json, **tkn, "height"))
			cylinder_data->height = token_to_double(json, *(++(*tkn)));
		else if (json_eq(json, **tkn, "radius"))
			cylinder_data->radius = token_to_double(json, *(++(*tkn)));
		else
			terminate("Unexpected key in cylinder");
		(*tkn)++;
	}
	add_object(&(*scene)->objects, object);
}
