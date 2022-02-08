/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 20:06:53 by rgelin            #+#    #+#             */
/*   Updated: 2021/12/24 16:15:13 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_dead(t_philo *philo, long current_meal)
{
	int	i;
	
	i = -1;
	if (philo->last_meal == 0)
		philo->last_meal = *(philo->start_time);
	while (++i < philo->nb_philo)
	{
		printf("%d %stime to die: %ld\n%s", philo[i].id_philo, RED, current_meal - philo[i].last_meal, NO_COLOR);
		if (current_meal - philo->last_meal > philo->time_to_die)
		{
			*(philo->die) = 1;
			// printf("%sdie time: %ld\n%s", RED, get_time() - *(philo->start_time), NO_COLOR);
			display_philo_message(philo, get_time() - *(philo->start_time), philo->id_philo, "died");
			return (1);
		}
	}
	return (0);
}

void	*dead_thread_function(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	printf("started\n");
	while (1)
	{
		if (ft_dead(philo, get_time()))
			return (NULL);
	}
	return (NULL);
}