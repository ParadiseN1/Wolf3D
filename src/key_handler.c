/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vprypesh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 20:35:02 by vprypesh          #+#    #+#             */
/*   Updated: 2018/09/11 20:35:03 by vprypesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	lets_go_up(t_params *m)
{
	double s;
	double delta;

	delta = 0.1;
	s = m->player.dir_x * m->ms * m->speedup;
	if (s < 0)
		delta *= -1;
	if (m->map[(int)(m->player.pos_x + s + delta)][(int)m->player.pos_y] == 0
	|| m->map[(int)(m->player.pos_x + s + delta)][(int)m->player.pos_y] == X)
		m->player.pos_x += s;
	s = m->player.dir_y * m->ms * m->speedup;
	if ((s < 0 && delta > 0) || (s > 0 && delta < 0))
		delta *= -1;
	if (m->map[(int)m->player.pos_x][(int)(m->player.pos_y + s + delta)] == 0
	|| m->map[(int)m->player.pos_x][(int)(m->player.pos_y + s + delta)] == X)
		m->player.pos_y += s;
}

void	lets_go_down(t_params *m)
{
	double s;
	double delta;

	delta = 0.1;
	s = m->player.dir_x * m->ms;
	if (s < 0)
		delta *= -1;
	if (m->map[(int)(m->player.pos_x - (s + delta))][(int)m->player.pos_y] == 0
	|| m->map[(int)(m->player.pos_x - (s + delta))][(int)m->player.pos_y] == X)
		m->player.pos_x -= s;
	s = m->player.dir_y * m->ms;
	if ((s < 0 && delta > 0) || (s > 0 && delta < 0))
		delta *= -1;
	if (m->map[(int)m->player.pos_x][(int)(m->player.pos_y - (s + delta))] == 0
	|| m->map[(int)m->player.pos_x][(int)(m->player.pos_y - (s + delta))] == X)
		m->player.pos_y -= s;
}

void	up_down(t_params *m, int side)
{
	static int	tmp;

	if (m->fps != tmp)
		play_step_sound(m, 1);
	tmp = m->fps;
	if (side == UP)
		lets_go_up(m);
	else if (side == DOWN)
		lets_go_down(m);
}

void	left_right(t_params *m, int side)
{
	double tmp;

	if (side == LEFT)
	{
		tmp = m->player.dir_x;
		m->player.dir_x = m->player.dir_x * cos(m->ang)
		- m->player.dir_y * sin(-m->ang);
		m->player.dir_y = tmp * sin(-m->ang) + m->player.dir_y * cos(-m->ang);
		tmp = m->player.plane_x;
		m->player.plane_x = m->player.plane_x * cos(-m->ang)
		- m->player.plane_y * sin(-m->ang);
		m->player.plane_y = tmp * sin(-m->ang)
		+ m->player.plane_y * cos(-m->ang);
	}
	else
	{
		tmp = m->player.dir_x;
		m->player.dir_x = m->player.dir_x * cos(m->ang)
		- m->player.dir_y * sin(m->ang);
		m->player.dir_y = tmp * sin(m->ang) + m->player.dir_y * cos(m->ang);
		tmp = m->player.plane_x;
		m->player.plane_x = m->player.plane_x * cos(m->ang)
		- m->player.plane_y * sin(m->ang);
		m->player.plane_y = tmp * sin(m->ang) + m->player.plane_y * cos(m->ang);
	}
}

void	key_system(SDL_Event e, t_params *m)
{
	if ((e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_w)
		&& e.key.type == SDL_KEYDOWN)
		up_down(m, UP);
	else if ((e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_s)
		&& e.key.type == SDL_KEYDOWN)
		up_down(m, DOWN);
	else if ((e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_a)
		&& e.key.type == SDL_KEYDOWN)
		left_right(m, LEFT);
	else if ((e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_d)
		&& e.key.type == SDL_KEYDOWN)
		left_right(m, RIGHT);
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_LSHIFT)
		m->speedup = 2;
	else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_LSHIFT)
		m->speedup = 1;
	if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
		m->game = 0;
	cast(m);
}
