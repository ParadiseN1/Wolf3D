/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vprypesh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 14:36:58 by vprypesh          #+#    #+#             */
/*   Updated: 2018/04/01 14:36:58 by vprypesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int		clear_img(t_params *m)
{
	Uint32		*pixels;
	int			i;

	i = -1;
	if (m == NULL)
		return (-1);
	pixels = (Uint32 *)m->img->pixels;
	while (++i < WIN_HEIGHT * WIN_WIDTH)
		pixels[i] = 0;
	return (1);
}

int		img_put_pixel(t_params *m, int x, int y, int color)
{
	Uint32	*pixels;

	if (x < 0 || y < 0 || x >= WIN_WIDTH || y >= WIN_HEIGHT || m->img == NULL)
		return (-1);
	SDL_LockSurface(m->img);
	pixels = (Uint32 *)m->img->pixels;
	pixels[y * WIN_WIDTH + x] = color;
	SDL_UnlockSurface(m->img);
	return (1);
}
