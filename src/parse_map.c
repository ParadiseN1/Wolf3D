/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vprypesh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 18:49:57 by vprypesh          #+#    #+#             */
/*   Updated: 2018/09/11 18:49:57 by vprypesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

char		*ft_strdup_read(char *src, int extra)
{
	char			*res;
	unsigned int	len;

	res = src;
	len = 1;
	while (*res)
	{
		res++;
		len++;
	}
	res = (char*)malloc(sizeof(char) * (len + extra));
	return (ft_strcpy(res, src));
}

int			ft_check_open_close(int fd)
{
	if (fd == -1)
		return (0);
	return (1);
}

char		*ft_record_from_file(int fd, char *str)
{
	char	*result;
	int		bufcharnum;
	char	readbuf[BUFLEN + 1];

	result = malloc(1);
	while ((bufcharnum = read(fd, readbuf, BUFLEN)))
	{
		str = ft_strdup_read(result, (bufcharnum + 1));
		str = ft_strncat(str, readbuf, bufcharnum);
		free(result);
		result = str;
	}
	return (result);
}

char		*parse_map(char *str)
{
	int		fd;
	int		check;
	char	*result;

	fd = open(str, O_RDONLY);
	check = ft_check_open_close(fd);
	if (check == 0)
		return (0);
	result = ft_record_from_file(fd, str);
	close(fd);
	check = ft_check_open_close(fd);
	if (check == 0)
		return (0);
	if (result[ft_strlen(result)] != '\n')
		ft_strcat(result, "\n");
	return (result);
}
