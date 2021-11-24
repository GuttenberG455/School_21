/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_stack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majacqua <majacqua@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:02:58 by majacqua          #+#    #+#             */
/*   Updated: 2021/11/24 12:50:46 by majacqua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	create_start_stack(t_lstack **stack, int argc, char **argv)
{
	int			i;
	t_lstack	*new;

	if (argc < 2)
		return (1);
	else
	{	
		i = 1;
		while (i < argc)
		{
			new = ft_create_list(ft_atoi(argv[i]));
			ft_push_list(stack, new);
			i++;
		}
		return (0);
	}
}
