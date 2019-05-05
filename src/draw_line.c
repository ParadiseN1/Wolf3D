/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vprypesh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 15:10:09 by vprypesh          #+#    #+#             */
/*   Updated: 2018/07/28 15:10:09 by vprypesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int		spawn_player(t_params *m)
{
	int i;
	int j;
	int k;

	k = 0;
	i = -1;
	while (++i < m->m_height)
	{
		j = -1;
		while (++j < m->m_width)
		{
			if (m->map[i][j] == 0 && k == 0)
			{
				m->player.pos_x = i + 0.5;
				m->player.pos_y = j + 0.5;
				k = 1;
			}
			if (m->map[i][j] < 0)
				m->map[i][j] = 0;
		}
	}
	return (k);
}

int		valid_format(char *file_name)
{
	int		i;
	char	*str;
	int		j;

	j = 0;
	str = malloc(sizeof(char) * ft_strlen(file_name));
	i = (int)ft_strlen(file_name) - 1;
	while (i >= 0 && file_name[i + 1] != '.')
	{
		str[j] = file_name[i];
		i--;
		j++;
	}
	str[j] = '\0';
	str = ft_strrev(str);
	if (ft_strcmp(str, ".txt") == 0 || ft_strcmp(str, ".wolf") == 0)
	{
		ft_strdel(&str);
		return (1);
	}
	ft_strdel(&str);
	return (-1);
}

void	cast_on_floor1(t_params *m)
{
	if (m->bmp == m->north || m->bmp == m->west)
		m->wall_x = m->player.pos_y + m->perp_wall_dist * m->ray_dir_y;
	else
		m->wall_x = m->player.pos_x + m->perp_wall_dist * m->ray_dir_x;
	m->wall_x -= (int)m->wall_x;
	if (m->bmp == m->north)
	{
		m->floor_x_wall = m->map_x;
		m->floor_y_wall = m->map_y + m->wall_x;
	}
	else if (m->bmp == m->west)
	{
		m->floor_x_wall = m->map_x + 1.0;
		m->floor_y_wall = m->map_y + m->wall_x;
	}
	else if (m->bmp == m->south)
	{
		m->floor_x_wall = m->map_x + m->wall_x;
		m->floor_y_wall = m->map_y;
	}
	else
	{
		m->floor_x_wall = m->map_x + m->wall_x;
		m->floor_y_wall = m->map_y + 1.0;
	}
}

void	cast_on_floor(int x, t_params *m)
{
	double	dist_wall;
	double	cur_dist;
	int		tex_x;
	int		tex_y;
	int		y;

	cast_on_floor1(m);
	dist_wall = m->perp_wall_dist;
	if (m->draw_end < 0)
		m->draw_end = WIN_HEIGHT;
	y = m->draw_end + 1;
	m->bmp = m->floor;
	while (y++ <= WIN_HEIGHT)
	{
		cur_dist = WIN_HEIGHT / (2.0 * y - WIN_HEIGHT);
		m->weight = cur_dist / dist_wall;
		m->cur_floor_x = m->weight * m->floor_x_wall
		+ (1.0 - m->weight) * m->player.pos_x;
		m->cur_floor_y = m->weight * m->floor_y_wall
		+ (1.0 - m->weight) * m->player.pos_y;
		tex_x = (int)(m->cur_floor_x * m->bmp->w) % m->bmp->w;
		tex_y = (int)(m->cur_floor_y * m->bmp->h) % m->bmp->h;
		img_put_pixel(m, x, y, get_color(m, tex_x, tex_y) >> 1 & 8355711);
		img_put_pixel(m, x, WIN_HEIGHT - y, get_color(m, tex_y, tex_x));
	}
}

int		draw_until(int x, int y0, int y1, t_params *m)
{
	int tmp;
	int height;

	height = y1 - y0;
	tmp = 0;
	if (y0 > y1)
	{
		tmp = y0;
		y0 = y1;
		y1 = tmp;
	}
	while (y0 < y1)
	{
		img_put_pixel(m, x, y0, texture_mapping2(m, height, y1 - y0));
		y0++;
	}
	return (1);
}
