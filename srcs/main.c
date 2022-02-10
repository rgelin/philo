/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:52:08 by rgelin            #+#    #+#             */
/*   Updated: 2022/02/10 17:03:43 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/*
A faire:
- gerer int min et int max dans les arguments
- nombre de fois philo mangent
- cas 1 seul philo
- leaks
- data race
- norminette
*/

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
	}
	if (pthread_create(&data->dead, NULL, &dead_thread_function, (void *)dead))
	{
		ft_perror("ERROR: couldn't create thread");
		return (-1);
	}
	data->die = 0;
	data->start_time = get_time();
	if (pthread_join(data->dead, NULL))
	{
		ft_perror("ERROR: pthread join\n");
		return (-1);
	}
	return (0);
}

// int	create_struct(char *av[], t_data *data, t_philo *philo, t_dead *dead)
// {
// 	data = (t_data *)malloc(sizeof(t_data));
// 	if (!data || init_struct_data(data, av))
// 	{
// 		ft_free(data, "ERROR: malloc");
// 		return (-1);
// 	}
// 	init_mutex_tab(data);
// 	philo = (t_philo *)malloc(sizeof(t_philo) * (data->nb_philo));
// 	dead = (t_dead *)malloc(sizeof(t_dead));
// 	if (!philo || !dead)
// 	{
// 		ft_free(data, "ERROR: malloc");
// 		return (-1);
// 	}
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
	philo = (t_philo *)malloc(sizeof(t_philo) * (data->nb_philo));
	dead = (t_dead *)malloc(sizeof(t_dead));
	if (!philo || !dead)
	{
		ft_free(data, "ERROR: malloc");
		return (-1);
	}
	init_philo(data, philo);
	init_struct_dead(data, &philo, dead);
	if (ft_create_threads(data, philo, dead))
	{
		// destroy_mutex(data);
		ft_free(data, "ERROR: thread");
		return (-1);
	}
	destroy_mutex(data);
	system("leaks philo");
	return (0);
}