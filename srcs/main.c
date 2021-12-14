/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:52:08 by rgelin            #+#    #+#             */
/*   Updated: 2021/12/14 16:17:55 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_struct_data(t_data *data, char *av[])
{
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->nb_time_eat = ft_atoi(av[5]);
	else
		data->nb_time_eat = 0;
}

void	init_philo(t_data *data, t_philo *philo)
{
	int i;

	i = -1;
	while (++i < data->nb_philo)
	{
		philo->id_philo = i + 1;
		if (i == 0)
			philo->left_fork = &data->mutex[data->nb_philo - 1];
		else
			philo->left_fork = &data->mutex[i - 1];
		philo->right_fork = &data->mutex[i];
	}
}

int	main(int ac, char *av[])
{
	t_data	*data;
	t_philo	*philo;

	if (check_error(ac, av))
	{
		ft_perror("ERROR: wrong arguments");
		return (-1);
	}
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (-1);
	init_struct_data(data, av);
	init_mutex_tab(data);
	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
	{
		free(data);
		return (-1);
	}
	init_philo(data, philo);
	//init philo
	
	

	// int i = -1;
	// while (++i < data->nb_philo)
	// 	printf("%p\n", data->mutex[i]);
		// printf("%p\n", data->mutex[i]);

		// printf("%p\n", data->mutex[0]);
	
	printf("nb_philo: %d\n", data->nb_philo);
	printf("time to die: %d\n", data->time_to_die);
	printf("time to eat: %d\n", data->time_to_eat);
	printf("time to sleep: %d\n", data->time_to_sleep);
	if (data->nb_time_eat)
		printf("nb time eat: %d\n", data->nb_time_eat);
}