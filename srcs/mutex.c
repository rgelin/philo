/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:39:19 by rgelin            #+#    #+#             */
/*   Updated: 2021/12/17 14:43:57 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_mutex_tab(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_init(&data->display, NULL);
	while (++i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->mutex[i], NULL))
		{
			ft_perror("ERROR: init mutex");
			return (-1);
		}
	}
	return (0);
}

int	destroy_mutex(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&data->display);
	if (data->mutex)
	{
		while (++i < data->nb_philo)
		{
			if (pthread_mutex_destroy(&data->mutex[i]))
			{
				ft_perror("ERROR: destroy mutex");
				return (-1);
			}
		}
	}
	return (0);
}

void	display_philo_message(t_philo *philo, long time, int id, char *msg)
{
	pthread_mutex_lock(philo->display);
	printf("%ld %d %s\n", time, id, msg);
	pthread_mutex_unlock(philo->display);
}
