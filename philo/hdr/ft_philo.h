/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-m <amaria-m@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:45:51 by amaria-m          #+#    #+#             */
/*   Updated: 2022/07/03 12:14:45 by amaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILO_H
# define FT_PHILO_H

# include <ft_string.h>
# include <ft_array.h>
# include <ft_list.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

# include <stdio.h> // printf

typedef struct s_info
{
	int				args[5];
	suseconds_t		start_t;
	int				dead;
	t_list			*mem;
	pthread_t		*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print;
	suseconds_t		time;
}					t_info;

typedef struct s_philo
{
	int				id;
	int				*args;
	t_list			*mem;
	suseconds_t		start_t;
	suseconds_t		end_t;
	int				*dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print;
	suseconds_t		*time;
}					t_philo;

// MAIN
void			*ft_routine(void *ptr);
int				ft_print(t_philo philo, char *msg);

// MEM
void			*ft_malloc(size_t size, t_list *lst);

// ARGS
int				ft_get_args(int argc, char **argv, int *args);

// TIME
suseconds_t		ft_get_time(void);
void			ft_sleep(t_philo *philo, suseconds_t waitime);
int				ft_verify_end(t_info *info, t_philo *philos);
void			ft_eat(t_philo *philo);

// THREADS && MUTEXES
int				ft_create_mutexes(t_info *info);
int				ft_create_threads(t_info *info);
#endif