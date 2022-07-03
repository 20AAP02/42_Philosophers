/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-m <amaria-m@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 17:20:25 by amaria-m          #+#    #+#             */
/*   Updated: 2022/07/03 12:24:03 by amaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_philo.h>

suseconds_t	ft_get_time(void)
{
	struct timeval	c_time;

	gettimeofday(&c_time, NULL);
	return (c_time.tv_usec);
}

void	ft_sleep(t_philo *philo, suseconds_t waitime)
{
	suseconds_t	start;
	suseconds_t	now;

	start = ft_get_time();
	while (!*(philo->dead))
	{
		now = ft_get_time();
		if (now - start >= waitime)
			break ;
		usleep(10);
	}
}

int	ft_verify_end(t_info *info, t_philo *philos)
{
	int	i;

	while (!info->dead)
	{
		i = -1;
		while (++i < info->args[0])
		{
			if (info->time >= philos[i].end_t)
			{
				ft_print(philos[i], "died");
				info->dead = 1;
				break ;
			}
		}
	}
	return (0);
}

int	ft_fork_index(t_philo *philo, int fork)
{
	if (!fork && philo->id % 2)
		return (philo->id - 1);
	if (!fork && philo->id == philo->args[0])
		return (0);
	if (!fork)
		return (philo->id);
	if (philo->id == philo->args[0])
		return (philo->id - 1);
	if (philo->id % 2)
		return (philo->id);
	return (philo->id - 1);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->forks[ft_fork_index(philo, 0)]);
	ft_print(*philo, "has taken a fork");
	if (philo->args[0] != 1)
	{
		pthread_mutex_lock(&philo->forks[ft_fork_index(philo, 1)]);
		ft_print(*philo, "has taken a fork");
		ft_print(*philo, "is eating");
		philo->end_t += philo->args[1];
		*(philo->time) += philo->args[2];
		ft_sleep(philo, (suseconds_t)philo->args[2]);
		pthread_mutex_unlock(&philo->forks[ft_fork_index(philo, 1)]);
	}
	pthread_mutex_unlock(&philo->forks[ft_fork_index(philo, 0)]);
}
