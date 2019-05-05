/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vprypesh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 13:45:30 by vprypesh          #+#    #+#             */
/*   Updated: 2018/07/28 13:45:30 by vprypesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	mini_cast2(t_params *m)
{
	if (m->side_dist_x < m->side_dist_y)
	{
		m->side_dist_x += m->delta_dist_x;
		m->map_x += m->step_x;
		m->side = 0;
		if (m->ray_dir_x > 0)
			m->bmp = m->north;
		else
			m->bmp = m->west;
	}
	else
	{
		m->side_dist_y += m->delta_dist_y;
		m->map_y += m->step_y;
		m->side = 1;
		if (m->ray_dir_y > 0)
			m->bmp = m->south;
		else
			m->bmp = m->east;
	}
}

void	mini_cast1(t_params *m)
{
	if (m->ray_dir_x < 0)
	{
		m->step_x = -1;
		m->side_dist_x = (m->player.pos_x - m->map_x) * m->delta_dist_x;
	}
	else
	{
		m->step_x = 1;
		m->side_dist_x = (m->map_x + 1.0 - m->player.pos_x) * m->delta_dist_x;
	}
	if (m->ray_dir_y < 0)
	{
		m->step_y = -1;
		m->side_dist_y = (m->player.pos_y - m->map_y) * m->delta_dist_y;
	}
	else
	{
		m->step_y = 1;
		m->side_dist_y = (m->map_y + 1.0 - m->player.pos_y) * m->delta_dist_y;
	}
	mini_cast2(m);
}

int		micro_cast(t_params *m, int x)
{
	if (m->side == 0)
		m->perp_wall_dist = (m->map_x - m->player.pos_x
			+ (1 - m->step_x) / 2) / m->ray_dir_x;
	else
		m->perp_wall_dist = (m->map_y - m->player.pos_y
			+ (1 - m->step_y) / 2) / m->ray_dir_y;
	if (m->perp_wall_dist == 0)
		return (0);
	m->line_height = (int)(WIN_HEIGHT / m->perp_wall_dist);
	m->draw_start = -m->line_height / 2 + WIN_HEIGHT / 2;
	m->draw_end = m->line_height / 2 + WIN_HEIGHT / 2;
	m->color = 0x0000FF;
	draw_until(x, m->draw_start, m->draw_end, m);
	m->side = -1;
	cast_on_floor(x, m);
	return (1);
}

void	prekol(t_params *m, int x)
{
	m->hit = 0;
	m->camera_x = 2 * x / (double)WIN_WIDTH - 1;
	m->ray_dir_x = m->player.dir_x + m->player.plane_x * m->camera_x;
	m->ray_dir_y = m->player.dir_y + m->player.plane_y * m->camera_x;
	m->delta_dist_x = fabs(1 / m->ray_dir_x);
	m->delta_dist_y = fabs(1 / m->ray_dir_y);
	m->map_x = (int)m->player.pos_x;
	m->map_y = (int)m->player.pos_y;
}

void	cast(t_params *m)
{
	int x;

	m->camera_x = 0;
	m->ray_dir_y = 0;
	m->ray_dir_x = 0;
	x = 0;
	while (x < WIN_WIDTH)
	{
		prekol(m, x);
		while (m->hit == 0)
		{
			mini_cast1(m);
			if (m->map_x < 0 || m->map_y < 0)
				break ;
			if (m->map[m->map_x][m->map_y] > 0)
				m->hit = 1;
		}
		if (m->hit == 1 && micro_cast(m, x) == 0)
			break ;
		x++;
	}
	if (m->perp_wall_dist == 0)
		m->player.pos_x--;
	render_text(m, ft_itoa(m->fps / 1000));
}
