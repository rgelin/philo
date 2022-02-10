/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 20:06:53 by rgelin            #+#    #+#             */
/*   Updated: 2022/02/10 16:59:06 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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

	while (*(dead->die))
		usleep(10);
	while (!*(dead->die))
	{
		if (ft_dead(dead))
			return (NULL);
	}
	return (NULL);
}