/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 20:06:53 by rgelin            #+#    #+#             */
/*   Updated: 2022/02/18 17:39:40 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	nb_times_eat_condition(t_dead *dead)
{
	// pthread_mutex_unlock(dead->dead_mutex);
	pthread_mutex_lock(dead->dead_mutex);
	*(dead->die) = 1;
	pthread_mutex_unlock(dead->dead_mutex);
	pthread_mutex_lock(dead->display);
	printf("Each philosopher has eaten at least %d times\n", dead->nb_time_eat);
	pthread_mutex_unlock(dead->display);
	return (1);
}

int	dead_condition(t_dead *dead, int i)
{
	// pthread_mutex_unlock(dead->dead_mutex);
	pthread_mutex_lock(dead->dead_mutex);
	// *(dead->philo[i].die) = 1;
	*(dead->die) = 1;
	pthread_mutex_unlock(dead->dead_mutex);
	display_philo_message(dead->philo, dead->philo[i].id_philo, "died");
	return (1);
}

int	ft_dead(t_dead *dead)
{
	int		i;
	long	time;

	i = -1;
	time = get_time();
	while (++i < dead->nb_philo)
	{
		if (dead->philo[i].last_meal == 0)
			dead->philo[i].last_meal = *(dead->philo[i].start_time);
		if (dead->nb_time_eat != -1 && dead->philo[i].nb_time_eat >= dead->nb_time_eat)
		{
			dead->philo[i].nb_time_eat = -10000;
			dead->nb_philo_finish_eating++;
			// printf("\n\nadress: %p\n\n", &dead->nb_philo_finish_eating);
		}
		if (dead->nb_philo_finish_eating >= dead->nb_philo)
			return (nb_times_eat_condition(dead));
		if ((long)(time - dead->philo[i].last_meal) > (long)dead->time_to_die)
			return (dead_condition(dead, i));
	}
	return (0);
}

void	*dead_thread_function(void *arg)
{
	t_dead *dead = (t_dead *)arg;

	pthread_mutex_lock(dead->dead_mutex);
	while (*(dead->die))
	{
		pthread_mutex_unlock(dead->dead_mutex);
		usleep(10);
		pthread_mutex_lock(dead->dead_mutex);
	}
	pthread_mutex_unlock(dead->dead_mutex);
	pthread_mutex_lock(dead->dead_mutex);
	while (!*(dead->die))
	{
		pthread_mutex_unlock(dead->dead_mutex);
		pthread_mutex_lock(dead->dead_mutex);
		if (ft_dead(dead))
			break ;
		pthread_mutex_unlock(dead->dead_mutex);
	}
	return (NULL);
}