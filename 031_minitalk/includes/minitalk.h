/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majacqua <majacqua@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 12:13:16 by majacqua          #+#    #+#             */
/*   Updated: 2022/01/12 17:43:45 by majacqua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <stdlib.h>
# include <unistd.h>
# include <signal.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

typedef struct s_message
{
	char	text_msg[BUFFER_SIZE];
	int		top_char;
	int		top_bit;
	int		buff_overflow;
	int		all_recieved;
}		t_message;

t_message	g_msg = {{0}, 0, 1 << 6, 0, 0};

void	ft_close(char *err_msg);

#endif
