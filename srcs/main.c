/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:52:08 by rgelin            #+#    #+#             */
/*   Updated: 2021/12/24 16:36:44 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_free(t_data *data, char *err_msg)
{
	if (data)
	{
		destroy_mutex(data);
		if (data->philo_thread)
			free(data->philo_thread);
	}
	if (err_msg)
		ft_perror(err_msg);
}

long	get_time(void)
{
	struct timeval time;
	
	gettimeofday(&time, NULL);
	return ((long)((time.tv_sec * 1000) + (time.tv_usec/1000)));
}

// void	init_struct_dead(t_data *data, t_philo *philo)
// {
	
// }

int	ft_create_threads(t_data *data, t_philo *philo)
{
	int i;
	
	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_create(&data->philo_thread[i], NULL, &routine_philo, (void *)&philo[i]))
		{
			ft_perror("ERROR: couldn't create thread");
			return (-1);
		}
		printf("thread %d created\n", i);
	}
	data->start_time = get_time();
	data->die = 0;
	// pthread_create(&data->dead, NULL, &dead_thread_function, (void *)&philo);
	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_join(data->philo_thread[i], NULL))
		{
			write(2, "ERROR: pthread join\n", 19);
			return (-1);
		}
	}
	return (0);
	// pthread_join(data->dead, NULL);
}

int	main(int ac, char *av[])
{
	t_data	*data;
	t_philo	*philo;
	// pthread *philo_thread;

	if (check_error(ac, av))
	{
		ft_perror("ERROR: wrong arguments");
		return (-1);
	}
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (-1);
	if (init_struct_data(data, av))
	{
		ft_free(data, "ERROR: malloc");
		return (-1);
	}
	init_mutex_tab(data);
	philo = (t_philo *)malloc(sizeof(t_philo) * data->nb_philo);
	if (!philo)
	{
		ft_free(data, "ERROR: malloc");
		return (-1);
	}
	init_philo(data, philo);
	if (ft_create_threads(data, philo))
		if (!philo)
	{
		ft_free(data, "ERROR: malloc");
		return (-1);
	}
	
	
	// i = -1;
	// while (++i < data->nb_philo)
	// 	printf("philo %d start time: %ld and end time: %ld\n", philo[i].id_philo, philo[i].start_time, philo[i].end_time);
	// printf("nb_philo: %d\n", data->nb_philo);
	// printf("time to die: %d\n", data->time_to_die);
	// printf("time to eat: %d\n", data->time_to_eat);
	// printf("time to sleep: %d\n", data->time_to_sleep);
	// if (data->nb_time_eat)
	// 	printf("nb time eat: %d\n", data->nb_time_eat);
	destroy_mutex(data);
}