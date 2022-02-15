/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:39:19 by rgelin            #+#    #+#             */
/*   Updated: 2022/02/15 17:19:40 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_mutex_tab(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_init(&data->display, NULL);
	pthread_mutex_init(&data->dead_mutex, NULL);
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
	// pthread_mutex_unlock(&data->display);
	pthread_mutex_destroy(&data->display);
	while (++i < data->nb_philo)
		pthread_mutex_unlock(&data->mutex[i]);
	i = -1;
	if (data->mutex)
	{
		while (++i < data->nb_philo)
		{
			if (pthread_detach(data->philo_thread[i]))
			{
				ft_perror("ERROR: detach thread philo");
				return (-1);
			}
			if (pthread_mutex_destroy(&data->mutex[i]))
			{
				ft_perror("ERROR: destroy mutex");
				return (-1);
			}
		}
	}
	// if (pthread_detach(data->dead))
	// {
	// 	ft_perror("ERROR: detach thread dead");
	// 	return (-1);
	// }
	return (0);
}

void	display_philo_message(t_philo *philo, int id, char *msg)
{
	long	time;
	pthread_mutex_lock(philo->display);
	time = get_time();
	// if (ft_strncmp(msg, "nb times", 8)
	// {
	// 	printf("Each philosopher has eaten at least %d times\n", philo->);	
	// }
		
	printf("%ld %d %s\n", time - *(philo->start_time), id, msg);
	if (ft_strncmp(msg, "died", 4))
		pthread_mutex_unlock(philo->display);
}
