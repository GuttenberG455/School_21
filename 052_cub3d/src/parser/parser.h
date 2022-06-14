/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majacqua <majacqua@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 16:23:25 by majacqua          #+#    #+#             */
/*   Updated: 2022/06/14 17:45:58 by majacqua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

# include <limits.h>
# include <fcntl.h>
# include <stdio.h>

# include "../env/env.h"
# include "../error/error.h"

void validate_input(int argc, char **argv);
void get_properties(t_map *map, int fd);
t_map *get_map(char *argv);

#endif