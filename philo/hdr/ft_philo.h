/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-m <amaria-m@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:45:51 by amaria-m          #+#    #+#             */
/*   Updated: 2022/07/05 15:33:26 by amaria-m         ###   ########.fr       */
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
	int				n;
	int				die_t;
	int				eat_t;
	int				sleep_t;
	int				eat_times;
	pthread_t		*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	t_list			*mem;
	int				destroy;
	int				start_t;
}					t_info;

// FT_INIT
void	*ft_malloc(size_t size, t_list *lst);
int		ft_get_args(int argc, char **argv, int *args);
int		ft_info_init(t_info *info, int *args);
int		ft_mutex_destroy(t_info *info);
int		ft_threads_init(t_info *info, int *args);

#endif