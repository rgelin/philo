/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:52:08 by rgelin            #+#    #+#             */
/*   Updated: 2022/02/09 17:24:00 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	get_time(void)
{
	struct timeval time;
	
	gettimeofday(&time, NULL);
	return ((long)((time.tv_sec * 1000) + (time.tv_usec/1000)));
}


int	ft_create_threads(t_data *data, t_philo *philo, t_dead *dead)
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
	if (pthread_create(&data->dead, NULL, &dead_thread_function, (void *)dead))
	{
		ft_perror("ERROR: couldn't create thread");
		return (-1);
	}
	data->start_time = get_time();
	data->die = 0;
	printf("%d\n", dead->philo[1].id_philo);
	// i = -1;
	// while (++i < data->nb_philo)
	// {
	// 	if (pthread_join(data->philo_thread[i], NULL))
	// 	{
	// 		write(2, "ERROR: pthread join\n", 19);
	// 		return (-1);
	// 	}
	// }
	pthread_join(data->dead, NULL);
	return (0);
}

// int	malloc_struct(char *av[], t_data *data, t_philo *philo, t_dead *dead)
// {
// 	data = (t_data *)malloc(sizeof(t_data));
// 	if (!data || init_struct_data(data, av))
// 	{
// 		ft_free(data, "ERROR: malloc");
// 		return (-1);
// 	}
// 	init_mutex_tab(data);
// 	philo = (t_philo *)malloc(sizeof(t_philo) * data->nb_philo);
// 	if (!philo)
// 	{
// 		ft_free(data, "ERROR: malloc");
// 		return (-1);
// 	}
// 	init_philo(data, philo);
// 	dead = (t_dead *)malloc(sizeof(t_dead));
// 	if (!dead)
// 	{
// 		ft_free(data, "ERROR: malloc");
// 		return (-1);
// 	}
// 	init_struct_dead(data, &philo, dead);
// 	return (0);
// }

int	main(int ac, char *av[])
{
	t_data	*data;
	t_philo	*philo;
	t_dead	*dead;

	if (check_error(ac, av))
	{
		ft_perror("ERROR: wrong arguments");
		return (-1);
	}
		data = (t_data *)malloc(sizeof(t_data));
	if (!data || init_struct_data(data, av))
	{
		ft_free(data, "ERROR: malloc");
		return (-1);
	}
	init_mutex_tab(data);
	philo = (t_philo *)malloc(sizeof(t_philo) * data->nb_philo);
	dead = (t_dead *)malloc(sizeof(t_dead));
	if (!philo || !dead)
	{
		ft_free(data, "ERROR: malloc");
		return (-1);
	}
	init_philo(data, philo);
	init_struct_dead(data, &philo, dead);
	printf("%d\n", dead->philo[2].id_philo);
	if (ft_create_threads(data, philo, dead))
	{
		ft_free(data, "ERROR: thread");
		return (-1);
	}
	// data->die = 1;
	destroy_mutex(data);
	ft_free(data, NULL);
}