/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 15:52:34 by rgelin            #+#    #+#             */
/*   Updated: 2022/02/18 17:39:34 by rgelin           ###   ########.fr       */
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
	{
		pthread_mutex_unlock(philo->dead_mutex);
		display_philo_message(philo, philo->id_philo, "is sleeping");
	}
	while ((sleeping - start < philo->time_to_sleep))
	{
		usleep(10);
		sleeping = get_time();
	}
	pthread_mutex_lock(philo->dead_mutex);
	if (!*(philo->die))
	{
		pthread_mutex_unlock(philo->dead_mutex);
		display_philo_message(philo, philo->id_philo, "is thinking");
	}
}

static void	lock_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->dead_mutex);
	if (philo->id_philo % 2)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->dead_mutex);
		if (*(philo->die))
		{
			pthread_mutex_unlock(philo->dead_mutex);
			return ;
		}
		// printf("\n\nadress: %p\n\n", philo->die);
		display_philo_message(philo, philo->id_philo, "has taken a fork");
		pthread_mutex_unlock(philo->dead_mutex);
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->dead_mutex);
		if (*(philo->die))
		{
			pthread_mutex_unlock(philo->dead_mutex);
			return ;
		}
		display_philo_message(philo, philo->id_philo, "has taken a fork");
		pthread_mutex_unlock(philo->dead_mutex);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->dead_mutex);
		if (*(philo->die))
		{
			pthread_mutex_unlock(philo->dead_mutex);
			return ;
		}
		pthread_mutex_unlock(philo->dead_mutex);
		display_philo_message(philo, philo->id_philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->dead_mutex);
		if (*(philo->die))
		{
			pthread_mutex_unlock(philo->dead_mutex);
			return ;
		}
		pthread_mutex_unlock(philo->dead_mutex);
		display_philo_message(philo, philo->id_philo, "has taken a fork");
	}
}

static void	philo_eat(t_philo *philo)
{
	long	start;
	long	eating;

	pthread_mutex_unlock(philo->dead_mutex);
	start = get_time();
	eating = 0;
	// printf("\n\nadress: %p\n\n", &eating);
	pthread_mutex_lock(philo->dead_mutex);
	if (!*(philo->die))
	{
		pthread_mutex_unlock(philo->dead_mutex);
		display_philo_message(philo, philo->id_philo, "is eating");	
	}
	pthread_mutex_lock(philo->dead_mutex);
	philo->last_meal = get_time();
	// printf("\n\nadress[%d]: %p\n\n", philo->id_philo, &philo->nb_time_eat);
	pthread_mutex_unlock(philo->dead_mutex);
	while ((eating - start < philo->time_to_eat))
	{
		usleep(10);
		eating = get_time();
	}
	pthread_mutex_lock(philo->dead_mutex);
	philo->nb_time_eat++;
	pthread_mutex_unlock(philo->dead_mutex);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}


void	*routine_philo(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	pthread_mutex_lock(philo->dead_mutex);
	while (*(philo->die))
	{
		pthread_mutex_unlock(philo->dead_mutex);
		usleep(10);
		pthread_mutex_lock(philo->dead_mutex);
	}
	pthread_mutex_unlock(philo->dead_mutex);
	pthread_mutex_lock(philo->dead_mutex);
	while (!*(philo->die))
	{
			pthread_mutex_unlock(philo->dead_mutex);
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