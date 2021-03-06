/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseema <lseema@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 08:07:57 by lseema            #+#    #+#             */
/*   Updated: 2021/05/17 22:25:33 by lseema           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "scene.h"
#include "token_actions.h"

void	terminate_sdl(t_sdl *sdl)
{
	if (sdl != NULL)
	{
		SDL_DestroyRenderer(sdl->ren);
		sdl->ren = NULL;
		SDL_DestroyWindow(sdl->win);
		SDL_Quit();
		free(sdl);
		sdl = NULL;
	}
}

int	main(int argc, char **argv)
{
	int			fd;
	char		*json;
	t_scene		*scene;
	t_sdl		*sdl;

	if (argc != 2)
		terminate(ERR_OPEN);
	if (is_file_format(argv[1], JSON_EXTENSION))
		terminate(ERR_FORMAT);
	fd = open(argv[1], O_RDONLY);
	if (fd <= 0)
		terminate(ERR_READ);
	json = read_all_text(fd);
	if (json == NULL)
		terminate(ERR_EMPTY_FILE);
	scene = init_scene();
	parse_json(json, &scene);
	free(json);
	if (scene->camera == NULL || scene->light == NULL \
		|| scene->objects == NULL)
		terminate("Invalid scene, or objects not found");
	sdl = init_sdl(scene->width, scene->height);
	main_loop(sdl, scene);
	terminate_sdl(sdl);
	free_scene(&scene);
}
