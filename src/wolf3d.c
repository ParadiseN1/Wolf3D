/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vprypesh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 13:22:22 by vprypesh          #+#    #+#             */
/*   Updated: 2018/07/28 13:22:22 by vprypesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	error_handler(int state)
{
	if (state == 0)
		ft_putstr("usage: ./wolf3d \"mapfile.txt / mapfile.wolf\"\n");
	else if (state == 1)
		ft_putstr("Map error! Please put in correct map!\n");
	else if (state == 2)
		ft_putstr("Faild to load texture!\n");
	exit(1);
}

void	more_init(t_params *m)
{
	m->sample = Mix_LoadWAV(WAV_STEP);
	if (!m->sample)
	{
		ft_putstr("Fail to load WAV\n");
		exit(0);
	}
	m->player.dir_x = 1;
	m->player.dir_y = 0;
	m->player.plane_x = 0;
	m->player.plane_y = FOV;
	m->player.view_ang = FOV * PI / 180;
	m->player.move_speed = 5;
	m->ms = 0.11;
	m->ang = 0.1;
	m->dst = (int)((WIN_WIDTH / 2) / tan(FOV / 2));
	m->left = 1;
	m->line_height = 0;
	m->cast_type = 0;
	m->fps = 0;
	m->speedup = 1;
	m->game = 1;
	m->time = 60;
	if (spawn_player(m) == 0)
		error_handler(1);
}

void	init_params(t_params *m)
{
	init_music(MP3_MUSIC, -1);
	m->win = SDL_CreateWindow("WOLF 3d", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	if (((m->map = str_to_int(ft_strsplit(m->file, '\n'), m)) == NULL)
		|| check_map(m->file) == 0)
		error_handler(1);
	m->bmp = NULL;
	if ((m->north = SDL_LoadBMP("resources/textures/b.bmp")) == NULL)
		error_handler(2);
	if ((m->south = SDL_LoadBMP("resources/textures/greystone.bmp")) == NULL)
		error_handler(2);
	if ((m->east = SDL_LoadBMP("resources/textures/colorstone.bmp")) == NULL)
		error_handler(2);
	if ((m->west = SDL_LoadBMP("resources/textures/redbrick.bmp")) == NULL)
		error_handler(2);
	if ((m->floor = SDL_LoadBMP("resources/textures/carpet.bmp")) == NULL)
		error_handler(2);
	m->color = 0x0000FF;
	m->side = 0;
	m->img = SDL_GetWindowSurface(m->win);
	m->start = 0;
	more_init(m);
}

int		hook_keydown(t_params *m)
{
	SDL_Event	e;

	while (m->game)
	{
		if (m->lastframe - m->start > 1000)
		{
			cast(m);
			m->start = m->lastframe;
			m->fps = m->time;
			m->time = 0;
		}
		else
		{
			m->lastframe = SDL_GetTicks();
			m->time++;
		}
		while (SDL_PollEvent(&e) != 0)
			key_system(e, m);
	}
	return (1);
}

int		main(int argc, char **argv)
{
	t_params *m;

	if (argc != 2 || valid_format(argv[1]) == -1)
		error_handler(0);
	m = malloc(sizeof(t_params));
	TTF_Init();
	m->font = TTF_OpenFont("./resources/font/OpenSans-Bold.ttf", 32);
	if (m->font == NULL)
	{
		ft_putstr("Invalid font!\n");
		exit(0);
	}
	if ((m->file = parse_map(argv[1])) == NULL)
	{
		ft_putstr("Invalid file name!\n");
		exit(0);
	}
	init_params(m);
	m->startclock = SDL_GetTicks();
	cast(m);
	hook_keydown(m);
	free_arr(m->map, m->m_height + 1);
	if (m->sample != NULL)
		Mix_FreeChunk(m->sample);
	return (0);
}
