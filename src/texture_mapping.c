/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vprypesh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 12:57:47 by vprypesh          #+#    #+#             */
/*   Updated: 2018/08/06 12:57:47 by vprypesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

Uint32			get_color(t_params *m, int x, int y)
{
	int		bpp;
	uint8_t *pixels;

	bpp = m->bmp->format->BytesPerPixel;
	pixels = (uint8_t *)m->bmp->pixels + y * m->bmp->pitch + x * bpp;
	if (bpp == 1)
		return (*pixels);
	if (bpp == 2)
		return (*(uint16_t *)pixels);
	if (bpp == 3)
	{
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return (pixels[0] << 16 | pixels[1] << 8 | pixels[2]);
		else
			return (pixels[0] | pixels[1] << 8 | pixels[2] << 16);
	}
	if (bpp == 4)
		return (*(uint32_t *)pixels);
	return (0);
}

double			texture_mapping2(t_params *m, int height, int line_height)
{
	static double	pxs;
	double			wall_x;
	double			k;
	Uint32			color;

	if (height == line_height)
		pxs = 0;
	(void)line_height;
	if (m->perp_wall_dist < 0.2)
		m->perp_wall_dist = 0.2;
	if (m->side == 0)
		wall_x = m->player.pos_y + m->perp_wall_dist * m->ray_dir_y;
	else
		wall_x = m->player.pos_x + m->perp_wall_dist * m->ray_dir_x;
	wall_x -= (int)wall_x;
	m->tex_x = (int)(wall_x * (double)(m->bmp->h));
	if ((m->side == 0 && m->ray_dir_x > 0)
		|| (m->side == 1 && m->ray_dir_y < 0))
		m->tex_x = m->bmp->w - m->tex_x - 1.0;
	k = ((double)height / (m->bmp->h));
	m->tex_y = pxs / k;
	pxs++;
	color = get_color(m, m->tex_x, m->tex_y);
	return (color);
}
