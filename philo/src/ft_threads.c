/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-m <amaria-m@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 15:45:20 by amaria-m          #+#    #+#             */
/*   Updated: 2022/07/06 13:45:53 by amaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_philo.h>

void	*ft_routine(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	while (!*(philo->destroy))
	{
		ft_eat(philo);
		philo->eat_times++;
		ft_print(philo, "is sleeping");
		ft_sleep(philo, (long long)philo->sleep_t);
		ft_print(philo, "is thinking");
	}
	return (NULL);
}

void	ft_print(t_philo *philo, char *msg)
{
	long long	now;

	pthread_mutex_lock(philo->print);
	now = (ft_get_time() - *(philo->start_t));
	if (!*(philo->destroy) || string().cmp(msg, "died"))
		printf("%lli %i %s\n", now, philo->id, msg);
	pthread_mutex_unlock(philo->print);
}

long long	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (long long)1000) + (time.tv_usec / 1000));
}

void	ft_check_philos(t_info *info)
{
	int	i;

	while (!info->destroy)
	{
		i = -1;
		while (++i < info->n)
		{
			if (info->philos[i].end_t <= (ft_get_time() - info->start_t))
			{
				info->destroy = 1;
				ft_print(&info->philos[i], "died");
				break ;
			}
		}
		i = -1;
		while (!info->destroy && info->eat_times != -1 && \
		info->eat_times <= info->philos[++i].eat_times)
			if (i == info->n - 1)
				info->destroy = 1;
	}
}

int	ft_threads_init(t_info *info, int *args)
{
	int	i;

	if (ft_info_init(info, args))
		return (1);
	i = -1;
	info->start_t = ft_get_time();
	while (++i < info->n)
		if (pthread_create(&info->threads[i], NULL, \
		ft_routine, &info->philos[i]) != 0)
			return (1);
	ft_check_philos(info);
	i = -1;
	while (++i < info->n)
		if (pthread_join(info->threads[i], NULL) != 0)
			return (1);
	if (ft_mutex_destroy(info))
		return (1);
	return (0);
}
