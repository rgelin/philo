/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:53:17 by rgelin            #+#    #+#             */
/*   Updated: 2021/12/15 15:25:25 by rgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>


typedef struct	s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_time_eat;
	// int				die;
	pthread_mutex_t	*mutex;
	pthread_t		*philo_thread;
}	t_data;

typedef struct	s_philo
{
	int				id_philo;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_time_eat;
	// int				*die;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	
}	t_philo;

//==============LIBFT_UTILS==============//

int		ft_strlen(char *str);
long	ft_atoi(const char *str);
int		ft_isdigit(int c);

//==============ERRORS==============//

int		check_error(int ac, char *av[]);
void	ft_perror(char *err_msg);

//==============MUTEX==============//

int		init_mutex_tab(t_data *data);
int		destroy_mutex(t_data *data);

#endif