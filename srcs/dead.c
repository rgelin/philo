/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 20:06:53 by rgelin            #+#    #+#             */
/*   Updated: 2022/02/09 16:54:56 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// int	ft_dead(t_philo *philo, long current_meal)
// {
// 	int	i;
	
// 	i = -1;
// 	if (philo->last_meal == 0)
// 		philo->last_meal = *(philo->start_time);
// 	while (++i < philo->nb_philo)
// 	{
// 		printf("%d %stime to die: %ld\n%s", philo[i].id_philo, RED, current_meal - philo[i].last_meal, NO_COLOR);
// 		if (current_meal - philo->last_meal > philo->time_to_die)
// 		{
// 			*(philo->die) = 1;
// 			// printf("%sdie time: %ld\n%s", RED, get_time() - *(philo->start_time), NO_COLOR);
// 			display_philo_message(philo, get_time() - *(philo->start_time), philo->id_philo, "died");
// 			return (1);
// 		}
// 	}
// 	return (0);
// }
int	ft_dead(t_dead *dead)
{
	int		i;
	long	time;

	i = -1;
	time = get_time();
	while (++i < dead->nb_philo)
	{
		// printf("last meal %ld\n", *(dead->philo[i].last_meal));
		// printf("time last meal[%d], %ld", dead->philo[i].id_philo, (time - dead->philo[i].last_meal));
		// return (1);
		if (dead->philo[i].last_meal == 0)
			dead->philo[i].last_meal = *(dead->philo[i].start_time);
		if ((long)(time - dead->philo[i].last_meal) > (long)dead->time_to_die)
		{
			*(dead->die) = 1;
			display_philo_message(dead->philo, time - *(dead->philo[i].start_time), dead->philo[i].id_philo, "died");
			return (1);
		}
	}
	return (0);
}

void	*dead_thread_function(void *arg)
{
	t_dead *dead = (t_dead *)arg;

	// printf("|| %d ||\n", *(dead->die));
	while (*(dead->die))
		usleep(10);
	// printf("|| %d ||\n", *(dead->die));
	while (!*(dead->die))
	{
		// printf("plop\n");
		if (ft_dead(dead))
			return (NULL);
	}
	return (NULL);
}