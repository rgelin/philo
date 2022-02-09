/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 15:52:34 by rgelin            #+#    #+#             */
/*   Updated: 2022/02/09 17:45:27 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// int	ft_dead(t_philo *philo, long current_meal)
// {
// 	if (philo->last_meal == 0)
// 		philo->last_meal = *(philo->start_time);
// 	// printf("%d %stime to die: %ld\n%s", philo->id_philo, RED, current_meal - philo->last_meal, NO_COLOR);
// 	if (current_meal - philo->last_meal > philo->time_to_die)
// 	{
// 		*(philo->die) = 1;
// 		// printf("%sdie time: %ld\n%s", RED, get_time() - *(philo->start_time), NO_COLOR);
// 		display_philo_message(philo, get_time() - *(philo->start_time), philo->id_philo, "died");
// 		return (1);
// 	}
// 	return (0);
// }

static void	philo_sleep(t_philo *philo)
{
	long	start;
	long	sleeping;

	start = get_time();
	sleeping = 0;
	if (!*(philo->die))
		display_philo_message(philo, start - *(philo->start_time), philo->id_philo, "is sleeping");
	usleep(philo->time_to_sleep * 1000);
	// while ((sleeping - start < philo->time_to_sleep))
	// {
	// 	sleeping = get_time();
	// 	// if (ft_dead(philo, sleeping))
	// 	// {
	// 	// 	printf("%ssleeping\n%s", GREEN, NO_COLOR);
	// 	// 	return ;
	// 	// }
	// }
	// printf("%d %stime sleep: %ld\n%s", philo->id_philo, GREEN, eating - start, NO_COLOR);
	if (!*(philo->die))
		display_philo_message(philo, get_time() - *(philo->start_time), philo->id_philo, "is thinking");
		// if (ft_dead(philo, start))
		// 	return ;
}

static void	lock_fork(t_philo *philo)
{
	// long time;

	// time = get_time();
	if (philo->id_philo % 2)
	{
		pthread_mutex_lock(philo->right_fork);
		display_philo_message(philo, get_time()- *(philo->start_time), philo->id_philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		display_philo_message(philo, get_time()- *(philo->start_time), philo->id_philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		display_philo_message(philo, get_time()- *(philo->start_time), philo->id_philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		display_philo_message(philo, get_time()- *(philo->start_time), philo->id_philo, "has taken a fork");
	}
}

static void	philo_eat(t_philo *philo)
{
	long	start;
	long	eating;
	// static long	last_meal;

	start = get_time();
	eating = 0;
	// printf("start time: %ld\n", *(philo->start_time));
	if (!*(philo->die))
		display_philo_message(philo, start - *(philo->start_time), philo->id_philo, "is eating");
	// printf("start eat: %ld || diff: %ld", start, start - *(philo->start_time));
	usleep(philo->time_to_eat * 1000);
	// while ((eating - start < philo->time_to_eat))
	// {
	// 	eating = get_time();
		
	// }
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}


void	*routine_philo(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	while (*(philo->die))
		usleep(10);
	// philo->last_meal = *(philo->start_time);
	while (!*(philo->die))
	{
			if (!*(philo->die))
				lock_fork(philo);
			if (!*(philo->die))
				philo_eat(philo);
			if (!*(philo->die))
				philo_sleep(philo);		
			// if (*(philo->die))
			// 	ft_died(philo);
	}
	return (NULL);
}