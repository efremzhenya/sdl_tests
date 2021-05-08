/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 14:46:15 by lseema            #+#    #+#             */
/*   Updated: 2021/05/08 16:33:03 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "token_actions.h"

t_vec3	get_normal_sphere(t_vec3 ray_dir, float closest_dist, struct s_object *obj, t_vec3 cam_origin)
{
	t_vec3 p;

	p = vec3_plus(cam_origin, vec3_mult_value(ray_dir, closest_dist));
	return (vec3_normalize(vec3_sub(p, obj->origin)));
}

void	parse_sphere(char const *json, jsmntok_t **tkn, t_scene **scene,
	int size)
{
	t_object		*object;
	t_sphere_data	*sphere_data;

	sphere_data = (t_sphere_data *)malloc(sizeof(t_sphere_data));
	object = new_object(sphere_data, OBJ_SPHERE, intersect_sphere);
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
		else if (json_eq(json, **tkn, "radius"))
			sphere_data->radius = token_to_double(json, *(++(*tkn)));
		else if (json_eq(json, **tkn, "specular"))
			object->specular =  token_to_double(json, *(++(*tkn)));
		else
			terminate("Unexpected key on sphere");
		(*tkn)++;
	}
	object->get_normal = get_normal_sphere;
	add_object(&(*scene)->objects, object);
}

float	intersect_sphere(t_vec3 cam_origin, t_vec3 ray_dir, t_object *sphere)
{
	t_vec3	cam_sphere;
	t_sphere_data	*params;
	t_quadric_eq	quadric;

	params = sphere->data;
	cam_sphere = vec3_sub(cam_origin, sphere->origin);
	quadric.a = vec3_dot_product(ray_dir, ray_dir);
	quadric.b = 2 * (vec3_dot_product(cam_sphere, ray_dir));
	quadric.c = vec3_dot_product(cam_sphere, cam_sphere)
		- pow(params->radius, 2);
	quadric.discr = (quadric.b * quadric.b) - (4 * quadric.a * quadric.c);
	if (quadric.discr >= 0)
	{
		quadric.root1 = ((-quadric.b) - sqrt(quadric.discr)) / 2.0;
		quadric.root2 = ((-quadric.b) + sqrt(quadric.discr)) / 2.0;
		if (quadric.root1 > 0)
			return (quadric.root1);
	}
	return (INFINITY);
}