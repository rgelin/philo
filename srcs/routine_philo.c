/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 15:52:34 by rgelin            #+#    #+#             */
/*   Updated: 2021/12/23 20:23:48 by rgelin           ###   ########.fr       */
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
	display_philo_message(philo, start - *(philo->start_time), philo->id_philo, "is sleeping");
	while (sleeping - start < philo->time_to_sleep)
	{
		sleeping = get_time();
		// if (ft_dead(philo, sleeping))
		// {
		// 	printf("%ssleeping\n%s", GREEN, NO_COLOR);
		// 	return ;
		// }
	}
	// printf("%d %stime sleep: %ld\n%s", philo->id_philo, GREEN, eating - start, NO_COLOR);
	if (!*(philo->die))
		display_philo_message(philo, get_time() - *(philo->start_time), philo->id_philo, "is thinking");
		// if (ft_dead(philo, start))
		// 	return ;
}


static void	philo_eat(t_philo *philo)
{
	long	start;
	long	eating;
	// static long	last_meal;

	start = get_time();
	// printf("philo %d: %ld\n", philo->id_philo, *(philo->start_time));
	eating = 0;
	// if (start  - last_meal  > philo->time_to_die)
	// {
	// 	*(philo->die) = 1;
	// 	return ;
	// }
	// usleep((useconds_t)philo->time_to_eat);
	// printf("%d last meal %ld\n", philo->id_philo, last_meal);
	// printf("\n");
	// printf("philo %d last_meal: %ld\n", philo->id_philo, philo->last_meal);
	// printf("philo %d start: %ld\n", philo->id_philo, start);
	// printf("philo %d diff: %ld < %ld", philo->id_philo, (start - philo->last_meal), (long)philo->time_to_die);
	// printf("\n");
	// printf("%d start %ld\n", philo->id_philo, start);
		// if (ft_dead(philo, start))
		// {
		// 	printf("%s%d eating\n%s", GREEN, philo->id_philo, NO_COLOR);
		// 	return ;
		// }
	// printf("%d last last_meal %ld\n", philo->id_philo, philo->last_meal);
	display_philo_message(philo, start - *(philo->start_time), philo->id_philo, "is eating");
	while (eating - start < philo->time_to_eat)
	{
		eating = get_time();
		
	}
	// printf("%d %stime eat: %ld\n%s", philo->id_philo, GREEN, eating - start, NO_COLOR);
		// if (ft_dead(philo, start))
		// 	return ;
	philo->last_meal = get_time();
	// printf("%d %slast meal: %ld\n%s", philo->id_philo, YELLOW, philo->last_meal, NO_COLOR);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	// printf("%d new last meal %ld\n", philo->id_philo, last_meal);
}

static void	lock_fork(t_philo *philo)
{
	if (philo->id_philo % 2)
	{
		pthread_mutex_lock(philo->right_fork);
		display_philo_message(philo, get_time() - *(philo->start_time), philo->id_philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		display_philo_message(philo, get_time() - *(philo->start_time), philo->id_philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		display_philo_message(philo, get_time() - *(philo->start_time), philo->id_philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		display_philo_message(philo, get_time() - *(philo->start_time), philo->id_philo, "has taken a fork");
	}
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
	}
	return (NULL);
}