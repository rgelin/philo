/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:52:08 by rgelin            #+#    #+#             */
/*   Updated: 2021/12/15 15:53:22 by rgelin           ###   ########.fr       */
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
	// data->die = 1;
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
		if (i == 0)
			philo[i].right_fork = &data->mutex[data->nb_philo - 1];
		else
			philo[i].right_fork = &data->mutex[i - 1];
		if (i == data->nb_philo - 1)
			philo[i].left_fork = &data->mutex[0];
		else
			philo[i].left_fork = &data->mutex[i];
		philo[i].nb_philo = data->nb_philo;
		philo[i].time_to_die = data->time_to_die;
		philo[i].time_to_eat = data->time_to_eat;
		philo[i].time_to_sleep = data->time_to_sleep;
		// philo[i].die = &data->die;
		if (data->nb_time_eat)
			philo[i].nb_time_eat = data->nb_time_eat;
	}
	
}

void	*routine_philo(void *arg)
{
	(void)arg;
	t_philo *philo = (t_philo *)arg;

	// while (1)
	// {
	// 	printf("Philo %d is thinking.\n", philo->id_philo);
	// 	if ()
	// }
	printf("id: %d\n", philo->id_philo);
	// printf("adresse die: %p\n", *(philo->die));
	printf("die: %d\n", philo->time_to_die);
	printf("rigth: %p\n", philo->right_fork);
	printf("left: %p\n", philo->left_fork);
	
	
	printf("\n\n");
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
		return (-1);
	init_mutex_tab(data);
	philo = (t_philo *)malloc(sizeof(t_philo) * data->nb_philo);
	if (!philo)
	{
		free(data);
		return (-1);
	}
	init_philo(data, philo);

	int	i;
	
	i = -1;
	while (++i < data->nb_philo)
	{
		printf("id main: %d\n", i);
		if (pthread_create(&data->philo_thread[i], NULL, &routine_philo, (void *)&philo[i]))
		{
			ft_perror("ERROR: couldn't create thread");
			return (-1);
		}
		sleep(1);
	}
	// int	i;

	// i = -1;
	// while (++i < data->nb_philo)
	// {
	// 	printf("%d\n", i);
	// 	if (pthread_mutex_init(&data->mutex[i], NULL))
	// 	{
	// 		ft_perror("ERROR: init mutex");
	// 		// return (-1);
	// 	}
	// }
	//init philo
	// i = -1;
	// while (++i < data->nb_philo)
	// {
	// 	sleep(1);
	// 	if (pthread_join(data->philo_thread[i], NULL))
	// 	{
	// 		write(2, "ERROR: pthread join\n", 19);
	// 		return (-1);
	// 	}
	// }
	

	// int i = -1;
	// while (++i < data->nb_philo)
	// 	printf("%p\n", data->mutex[i]);
		// printf("%p\n", data->mutex[i]);

		// printf("%p\n", &data->mutex[0]);
	
	printf("nb_philo: %d\n", data->nb_philo);
	printf("time to die: %d\n", data->time_to_die);
	printf("time to eat: %d\n", data->time_to_eat);
	printf("time to sleep: %d\n", data->time_to_sleep);
	if (data->nb_time_eat)
		printf("nb time eat: %d\n", data->nb_time_eat);
	destroy_mutex(data);
}