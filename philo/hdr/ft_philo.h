/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-m <amaria-m@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:45:51 by amaria-m          #+#    #+#             */
/*   Updated: 2022/07/01 20:26:42 by amaria-m         ###   ########.fr       */
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
	t_list			*mem;
	pthread_t		*philos;
	pthread_mutex_t	*forks;
	struct timeval	*time;
}					t_info;

typedef struct s_philo
{
	struct timeval	time;
	int				number;
	int				n_philos;
	int				die_t;
	int				eat_t;
	int				sleep_t;
	int				opt;
}					t_philo;

// MEM
void			*ft_malloc(size_t size, t_list *lst);

// ARGS
int				ft_get_args(int argc, char **argv, int *args);

// THREADS & MUTEXES
pthread_mutex_t	*ft_inisialise_mutexes(int n_forks, t_list *lst);
void			ft_destroy_mutexes(pthread_mutex_t	*forks, int n_forks);
int				ft_crt_threads(t_info *info, void *(*f)(void *), t_list *mem);

#endif