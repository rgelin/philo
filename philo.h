/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgelin <rgelin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:53:17 by rgelin            #+#    #+#             */
/*   Updated: 2022/02/09 17:04:44 by rgelin           ###   ########.fr       */
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

# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define NO_COLOR "\x1b[0m"

typedef struct	s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_time_eat;
	int				die;
	long			start_time;
	pthread_mutex_t	*mutex;
	pthread_t		*philo_thread;
	pthread_t		dead;
	pthread_mutex_t	display;
}	t_data;

typedef struct	s_philo
{
	int				id_philo;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_time_eat;
	int				*die;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*display;
	long			*start_time;
	long			last_meal;	
}	t_philo;

typedef struct s_dead
{
	int		nb_philo;
	int		time_to_die;
	int		*die;
	t_philo *philo;
}	t_dead;

//==============LIBFT_UTILS==============//

int		ft_strlen(char *str);
long	ft_atoi(const char *str);
int		ft_isdigit(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

//==============ERRORS==============//

int		check_error(int ac, char *av[]);
void	ft_perror(char *err_msg);
void	ft_free(t_data *data, char *err_msg);

//==============MUTEX==============//

int		init_mutex_tab(t_data *data);
int		destroy_mutex(t_data *data);
void	display_philo_message(t_philo *philo, long time, int id, char *msg);

//==============MAIN==============//
int		init_struct_data(t_data *data, char *av[]);
void	init_philo(t_data *data, t_philo *philo);
void	init_struct_dead(t_data *data, t_philo **philo, t_dead *dead);
long	get_time(void);
void	*routine_philo(void *arg);

void	*dead_thread_function(void *arg);

#endif