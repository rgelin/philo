/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:52:08 by rgelin            #+#    #+#             */
/*   Updated: 2021/12/16 17:50:00 by rgelin           ###   ########.fr       */
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

// suseconds_t	get_time(void)
// {
// 	struct timeval time;
	
// 	gettimeofday(&time, NULL);
// 	return ((time.tv_sec * 1000000) + time.tv_usec);
// }
long	get_time(void)
{
	struct timeval time;
	
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec/1000));
}

void	philo_sleep(t_philo *philo)
{
	long	start;
	long	eating;

	start = get_time();
	eating = 0;
	printf("%ld %d is sleeping\n", start - philo->start_time, philo->id_philo);
	while (eating - start < philo->time_to_sleep)
		eating = get_time();
}

void	philo_eat(t_philo *philo)
{
	long	start;
	long	eating;

	start = get_time();
	// printf("philo %d: %ld\n", philo->id_philo, philo->start_time);
	eating = 0;
	printf("%ld %d is eating\n", start - philo->start_time, philo->id_philo);
	while (eating - start < philo->time_to_eat)
		eating = get_time();
}

void	*routine_philo(void *arg)
{
	(void)arg;
	t_philo *philo = (t_philo *)arg;
	// int	i;
	while (*(philo->die))
		usleep(50);
	philo->start_time = get_time();
	// int time;
	// time = get_time();
	
	// printf("philo %d: diff %ld\n", philo->id_philo, (time - philo->start_time));
	// printf("%d start: %ld\n", philo->id_philo, philo->start_time);
	while (1)
	{
		if (philo->id_philo % 2)
		{
			pthread_mutex_lock(philo->right_fork);
			printf("%ld %d has taken a fork rigth\n", get_time() - philo->start_time, philo->id_philo);
			pthread_mutex_lock(philo->left_fork);
			printf("%ld %d has taken a fork left\n", get_time() - philo->start_time, philo->id_philo);
		}
		else
		{
			pthread_mutex_lock(philo->left_fork);
			printf("%ld %d has taken a fork left\n", get_time() - philo->start_time, philo->id_philo);
			pthread_mutex_lock(philo->right_fork);
			printf("%ld %d has taken a fork rigth\n", get_time() - philo->start_time, philo->id_philo);
		}
		philo_eat(philo);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		philo_sleep(philo);
		printf("%ld %d is thinking\n", get_time() - philo->start_time, philo->id_philo);
	}
	return (NULL);
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

	int i;
	
	i = -1;
	while (++i < data->nb_philo)
	{
		// printf("id main: %d\n", i);
		if (pthread_create(&data->philo_thread[i], NULL, &routine_philo, (void *)&philo[i]))
		{
			ft_perror("ERROR: couldn't create thread");
			return (-1);
		}
		printf("thread %d created\n", i);
		// sleep(1);
	}
	data->die = 0;
	
	i = -1;
	while (++i < data->nb_philo)
	{
		// sleep(1);
		if (pthread_join(data->philo_thread[i], NULL))
		{
			write(2, "ERROR: pthread join\n", 19);
			return (-1);
		}
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