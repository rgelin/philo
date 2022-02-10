/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 17:06:55 by rgelin            #+#    #+#             */
/*   Updated: 2022/02/10 18:03:33 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_struct_data(t_data *data, char *av[])
{
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->nb_time_eat = ft_atoi(av[5]);
	else
		data->nb_time_eat = 0;
	data->die = 1;
	data->start_time = 0;
	data->mutex = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->mutex)
		return (-1);
	data->philo_thread = malloc(sizeof(pthread_t) * data->nb_philo);
	if (!data->philo_thread)
		return (-1);
	return (0);
}

void	init_philo(t_data *data, t_philo *philo)
{
	int i;

	i = -1;
	while (++i < data->nb_philo)
	{
		philo[i].id_philo = i + 1;
		philo[i].right_fork = &data->mutex[i];
		if (i == data->nb_philo - 1)
			philo[i].left_fork = &data->mutex[0];
		else
			philo[i].left_fork = &data->mutex[i + 1];
		philo[i].nb_philo = data->nb_philo;
		philo[i].time_to_die = data->time_to_die;
		philo[i].time_to_eat = data->time_to_eat;
		philo[i].time_to_sleep = data->time_to_sleep;
		philo[i].die = &data->die;
		philo[i].start_time = &data->start_time;
		if (data->nb_time_eat)
			philo[i].nb_time_eat = data->nb_time_eat;
		philo[i].display = &data->display;
		philo[i].dead_mutex = &data->dead_mutex;
	}
}

void	init_struct_dead(t_data *data, t_philo **philo, t_dead *dead)
{
	dead->nb_philo= data->nb_philo;
	dead->time_to_die = data->time_to_die;
	dead->philo = *(philo);
	dead->die = &data->die;
}
