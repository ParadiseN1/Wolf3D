/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vprypesh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 15:34:45 by vprypesh          #+#    #+#             */
/*   Updated: 2017/09/26 15:34:46 by vprypesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s11;
	unsigned char	*s22;
	int				i;
	int				j;

	s11 = (unsigned char *)s1;
	s22 = (unsigned char *)s2;
	i = 0;
	j = 0;
	if (n == 0)
		return (0);
	while (i < (int)n && s11[i] != '\0')
	{
		if (s11[i] != s22[j])
			return (s11[i] - s22[j]);
		j++;
		i++;
		if (i == (int)n)
			return (0);
	}
	return ('\0' - s22[j]);
}
