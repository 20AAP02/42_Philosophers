/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-m <amaria-m@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 15:45:20 by amaria-m          #+#    #+#             */
/*   Updated: 2022/07/05 16:53:26 by amaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_philo.h>

void	*ft_routine(void *ptr)
{
	t_philo	*philo;
	int		i;

	philo = ptr;
	i = 0;
	while (!*(philo->destroy))
	{
		if (i > 0)
			break ;
		pthread_mutex_lock(philo->print);
		if (!*(philo->destroy))
			printf("%lli %i %s", (ft_get_time() - *(philo->start_t)), \
			philo->id, "bla\n");
		pthread_mutex_unlock(philo->print);
		i++;
	}
	return (NULL);
}

void	ft_print(t_philo *philo, char *msg)
{
	pthread_mutex_lock(philo->print);
	if (!*(philo->destroy))
		printf("%lli %i %s", (ft_get_time() - *(philo->start_t)), \
		philo->id, msg);
	pthread_mutex_unlock(philo->print);
}

long long	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec);
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
				printf("%lli %i %s\n", info->philos[i].end_t, i + 1, "died");
				break ;
			}
		}
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
