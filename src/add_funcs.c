/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vprypesh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 13:36:25 by vprypesh          #+#    #+#             */
/*   Updated: 2018/07/29 13:36:25 by vprypesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int			check_map(char *str)
{
	if (str[ft_strlen(str) - 1] != '\n')
		return (0);
	return (1);
}

int			get_num(char *str, int i)
{
	int		j;
	char	num[10000];
	int		res;

	j = 0;
	res = 0;
	while (str[i] != ' ' && str[i] != '\0' && str[i] != ',')
	{
		num[j] = str[i];
		i++;
		j++;
	}
	num[j] = '\0';
	res = abs(atoi(num));
	if (res < 0)
		res = 0;
	if ((ft_strlen(num) == 1 && num[0] == 'x'))
		return (-1);
	return (res);
}

int			get_next_value(char **file, int row, int value)
{
	int count;
	int i;
	int res;

	count = 0;
	i = 0;
	res = 0;
	while (file[row][i] != '\0')
	{
		if (file[row][i] != ' ' && ((i == 0)
		|| file[row][i - 1] == ' ') && file[row][i] != '\0')
			count++;
		if (count == value + 1)
			return (get_num(file[row], i));
		i++;
	}
	return (0);
}
