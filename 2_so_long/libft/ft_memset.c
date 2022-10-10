/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majacqua <majacqua@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 16:31:07 by majacqua          #+#    #+#             */
/*   Updated: 2021/10/09 11:43:31 by majacqua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *memptr, int val, size_t size)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *) memptr;
	while (i < size)
	{
		str[i] = (unsigned char) val;
		i++;
	}
	return ((void *) str);
}
