/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majacqua <majacqua@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 13:57:42 by majacqua          #+#    #+#             */
/*   Updated: 2022/03/16 19:09:57 by majacqua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_all_fed(t_env *env)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&env->meal_check);
	while (env->num_eat != -1 && i < env->philo_count
		&& env->philos[i].eat_count >= env->num_eat)
		i++;
	if (i == env->philo_count)
	{
		env->end_all_fed = 1;
		pthread_mutex_unlock(&env->meal_check);
		return (1);
	}
	pthread_mutex_unlock(&env->meal_check);
	return (0);
}

void	check_end(t_env *env, t_philo *philo)
{
	int		i;

	while (1)
	{
		i = -1;
		while (++i < env->philo_count)
		{
			pthread_mutex_lock(&env->meal_check);
			if (get_timestamp() - philo[i].last_time_eat > env->time_death)
			{
				print_death(env, philo->id);
				pthread_mutex_lock(&env->death_check);
				env->end_death = 1;
				pthread_mutex_unlock(&env->death_check);
				pthread_mutex_unlock(&env->meal_check);
				return ;
			}
			pthread_mutex_unlock(&env->meal_check);
		}
		if (check_all_fed(env))
			break ;
	}
}

void	*start_thread(void *void_philo)
{
	int		i;
	t_env	*env;
	t_philo	*philo;

	i = 0;
	philo = (t_philo *) void_philo;
	env = philo->env;
	if (philo->id % 2)
		usleep(10000);
	while (1)
	{
		if (death_thr_check(env) || meal_thr_check(env))
			break ;
		act_eat(philo);
		if (meal_thr_check(env) || death_thr_check(env))
			break ;
		print_action(env, philo->id, ST_SLEEP);
		thread_sleep(env->time_sleep);
		print_action(env, philo->id, ST_THINK);
		i++;
	}
	return (0);
}

void	exit_launch(t_env *env, t_philo *philo)
{
	int	i;

	i = 0;
	(void) philo;
	while (i < env->philo_count)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < env->philo_count)
	{
		pthread_mutex_destroy(&env->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&env->print_check);
	pthread_mutex_destroy(&env->meal_check);
	pthread_mutex_destroy(&env->death_check);
}

int	launch(t_env *env)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = env->philos;
	env->start_time = get_timestamp();
	while (i < env->philo_count)
	{
		if (pthread_create(&philo[i].thread, 0, start_thread, &philo[i]))
			return (1);
		pthread_mutex_lock(&env->meal_check);
		philo[i].last_time_eat = get_timestamp();
		pthread_mutex_unlock(&env->meal_check);
		i++;
	}
	check_end(env, env->philos);
	exit_launch(env, philo);
	return (0);
}
