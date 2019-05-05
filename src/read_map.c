/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vprypesh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 15:37:51 by vprypesh          #+#    #+#             */
/*   Updated: 2018/07/28 15:37:51 by vprypesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void		clear_arr(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

int			**str_to_int2(char **file, t_params *m, int **d, int prev)
{
	int j;
	int i;

	i = 0;
	while (i < count_heigth(file))
	{
		j = -1;
		d[i] = malloc(sizeof(int) * count_width(file[i]));
		while (++j < count_width(file[i]))
			d[i][j] = get_next_value(file, i, j);
		if ((prev != -1 && prev != j) ||
			((d[i][j - 1] == 0 || d[i][0] == 0
				|| d[i][j - 1] == X || d[i][0] == X)))
		{
			free_arr(d, i + 1);
			return (NULL);
		}
		prev = j;
		i++;
	}
	m->m_height = i - 1;
	m->m_width = j;
	return (d);
}

int			**str_to_int(char **file, t_params *m)
{
	int **digits;
	int prev;
	int last;

	last = 0;
	prev = -1;
	digits = malloc(sizeof(int *) * count_heigth(file));
	digits = str_to_int2(file, m, digits, prev);
	if (digits != NULL && (check_fist_n_last(digits, m) == 0
		|| m->m_height > MAX_SIZE || m->m_width > MAX_SIZE))
	{
		free_arr(digits, m->m_height + 1);
		clear_arr(file);
		return (NULL);
	}
	clear_arr(file);
	return (digits);
}

void		del_str(char *str)
{
	ft_bzero(str, ft_strlen(str));
	ft_strdel(&str);
}
