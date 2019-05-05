/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vprypesh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 12:42:43 by vprypesh          #+#    #+#             */
/*   Updated: 2018/09/05 12:42:43 by vprypesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int			count_width(char *str)
{
	int i;
	int count;

	i = 0;
	count = 1;
	while (str[i] != '\0')
	{
		if (str[i] == ' ' && (str[i + 1] != ' ' || str[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

int			count_heigth(char **matrix)
{
	int i;

	i = 0;
	while (matrix[i])
	{
		i++;
	}
	return (i);
}

void		free_arr(int **arr, int height)
{
	int i;

	i = 0;
	while (i < height)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

int			check_fist_n_last(int **digits, t_params *m)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (digits == NULL)
		return (0);
	while (j < m->m_width)
	{
		if (digits[i][j] == 0 || digits[i][j] == X)
			return (0);
		j++;
	}
	i = m->m_height;
	j = 0;
	while (j < m->m_width)
	{
		if (digits[i][j] == 0 || digits[i][j] == X)
			return (0);
		j++;
	}
	return (1);
}
