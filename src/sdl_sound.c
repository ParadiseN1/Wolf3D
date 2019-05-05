/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_sound.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vprypesh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 20:34:42 by vprypesh          #+#    #+#             */
/*   Updated: 2018/09/11 20:34:42 by vprypesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void		init_music(char *path, int mode)
{
	int			res;
	Mix_Music	*music;

	res = 0;
	if (mode == -1 && SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		ft_putstr("Failed to init Audio!\n");
		exit(0);
	}
	res = Mix_Init(MIX_INIT_MP3);
	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
	music = Mix_LoadMUS(path);
	Mix_PlayMusic(music, mode);
}

void		play_step_sound(t_params *m, int loop)
{
	if (Mix_PlayChannel(1, m->sample, loop) == -1)
	{
		ft_putstr("WAV play error!\n");
		exit(0);
	}
}

void		render_text(t_params *m, char *str)
{
	SDL_Color	color;
	SDL_Surface	*text;

	if (TTF_Init() != 0)
	{
		ft_putstr("FAIL TO LOAD TTF\n");
		exit(0);
	}
	if (m->font == NULL)
	{
		ft_putstr("FAIL TO LOAD FONT!\n");
		exit(0);
	}
	color = (SDL_Color){255, 255, 255, 0};
	text = TTF_RenderText_Solid(m->font, str, color);
	SDL_BlitSurface(text, NULL, m->img, NULL);
	SDL_FreeSurface(text);
	SDL_UpdateWindowSurface(m->win);
	free(str);
}
