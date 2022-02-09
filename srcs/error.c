/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:31:59 by rgelin            #+#    #+#             */
/*   Updated: 2022/02/09 15:38:34 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_perror(char *err_msg)
{
	write(2, err_msg, ft_strlen(err_msg));
	write(2, "\n", 1);
}

int	check_error(int ac, char *av[])
{
	int	i;
	int	j;
	
	if (ac != 5 && ac != 6)
		return (1);
	i = 0;
	while (++i < ac)
	{
		j = -1;
		if (ft_atoi(av[i]) >= INT_MAX)
			return (-1);
		while (av[i][++j])
		{
			if (ft_isdigit(av[i][j]) == 0)
				return (1);
		}
	}
	return (0);
}

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
