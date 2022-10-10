/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majacqua <majacqua@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 16:59:07 by majacqua          #+#    #+#             */
/*   Updated: 2022/03/15 14:16:11 by majacqua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->philo_count)
	{
		if (pthread_mutex_init(&env->forks[i], 0))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&env->meal_check, 0))
		return (1);
	if (pthread_mutex_init(&env->print_check, 0))
		return (1);
	if (pthread_mutex_init(&env->death_check, 0))
		return (1);
	return (0);
}

int	init_philos(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->philo_count)
	{
		env->philos[i].id = i;
		env->philos[i].env = env;
		env->philos[i].left_fork = i;
		env->philos[i].right_fork = (i + 1) % env->philo_count;
		env->philos[i].eat_count = 0;
		env->philos[i].last_time_eat = 0;
		i++;
	}
	return (0);
}

int	init_env(t_env *env, char **argv)
{
	env->philo_count = ft_atoi(argv[1]);
	env->time_death = ft_atoi(argv[2]);
	env->time_eat = ft_atoi(argv[3]);
	env->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
	{
		env->num_eat = ft_atoi(argv[5]);
		if ((env->num_eat <= 0) && (argv[5][0] != '0'))
			return (1);
	}
	else
		env->num_eat = -1;
	env->end_death = 0;
	env->end_all_fed = 0;
	if (env->philo_count <= 0 || env->philo_count > 322 || env->time_death < 0
		|| env->time_eat < 0 || env->time_sleep < 0)
		return (1);
	init_philos(env);
	if (init_mutex(env))
		return (1);
	return (0);
}
