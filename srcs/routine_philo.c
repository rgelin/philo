/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 15:52:34 by rgelin            #+#    #+#             */
/*   Updated: 2022/02/10 16:58:51 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	philo_sleep(t_philo *philo)
{
	long	start;
	long	sleeping;

	pthread_mutex_unlock(philo->dead_mutex);
	start = get_time();
	sleeping = 0;
	pthread_mutex_lock(philo->dead_mutex);
	if (!*(philo->die))
		display_philo_message(philo, start - *(philo->start_time), philo->id_philo, "is sleeping");
	pthread_mutex_unlock(philo->dead_mutex);
	while ((sleeping - start < philo->time_to_sleep))
	{
		usleep(10);
		sleeping = get_time();
	}
	pthread_mutex_lock(philo->dead_mutex);
	if (!*(philo->die))
		display_philo_message(philo, get_time() - *(philo->start_time), philo->id_philo, "is thinking");
	pthread_mutex_unlock(philo->dead_mutex);
}

static void	lock_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->dead_mutex);
	if (philo->id_philo % 2)
	{
		pthread_mutex_lock(philo->right_fork);
		if (!*(philo->die))
			display_philo_message(philo, get_time()- *(philo->start_time), philo->id_philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		if (!*(philo->die))
			display_philo_message(philo, get_time()- *(philo->start_time), philo->id_philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		if (!*(philo->die))
			display_philo_message(philo, get_time()- *(philo->start_time), philo->id_philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		if (!*(philo->die))
			display_philo_message(philo, get_time()- *(philo->start_time), philo->id_philo, "has taken a fork");
	}
}

static void	philo_eat(t_philo *philo)
{
	long	start;
	long	eating;

	pthread_mutex_unlock(philo->dead_mutex);
	start = get_time();
	eating = 0;
	pthread_mutex_lock(philo->dead_mutex);
	if (!*(philo->die))
		display_philo_message(philo, start - *(philo->start_time), philo->id_philo, "is eating");
	pthread_mutex_unlock(philo->dead_mutex);
	while ((eating - start < philo->time_to_eat))
	{
		usleep(10);
		eating = get_time();
	}
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}


void	*routine_philo(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	pthread_mutex_lock(philo->dead_mutex);
	while (*(philo->die))
		usleep(10);
	pthread_mutex_unlock(philo->dead_mutex);
	while (!*(philo->die))
	{
			pthread_mutex_lock(philo->dead_mutex);
			if (!*(philo->die))
				lock_fork(philo);
			pthread_mutex_lock(philo->dead_mutex);
			if (!*(philo->die))
				philo_eat(philo);
			pthread_mutex_lock(philo->dead_mutex);
			if (!*(philo->die))
				philo_sleep(philo);
	}
	return (NULL);
}