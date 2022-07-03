/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-m <amaria-m@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 18:02:31 by amaria-m          #+#    #+#             */
/*   Updated: 2022/07/03 12:18:05 by amaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_philo.h>

static void	ft_set_philo(t_philo *philo, t_info *info, int id)
{
	philo->id = id;
	philo->args = info->args;
	philo->mem = info->mem;
	philo->start_t = 0;
	philo->time = &info->time;
	philo->dead = &info->dead;
	philo->end_t = (suseconds_t)info->args[1];
	philo->forks = info->forks;
	philo->print = info->print;
}

int	ft_destroy_mutexes(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->args[0])
		if (pthread_mutex_destroy(&info->forks[i]) != 0)
			return (3);
	if (pthread_mutex_destroy(info->print) != 0)
		return (3);
	return (0);
}

void	*ft_routine(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	while (!*(philo->dead))
	{
		ft_eat(philo);
		ft_print(*philo, "is sleeping");
		ft_sleep(philo, (suseconds_t)philo->args[3]);
		*(philo->time) += philo->args[3];
		ft_print(*philo, "is thinking");
	}
	return (NULL);
}

int	ft_create_threads(t_info *info)
{
	t_philo	*philos;
	int		i;

	info->dead = 0;
	info->time = 0;
	info->philos = ft_malloc(sizeof(pthread_t) * info->args[0], info->mem);
	philos = ft_malloc(sizeof(t_philo) * info->args[0], info->mem);
	i = -1;
	while (++i < info->args[0])
		ft_set_philo(&philos[i], info, i + 1);
	i = -1;
	while (++i < info->args[0])
		if (pthread_create(&info->philos[i], NULL, ft_routine, &philos[i]) != 0)
			return (1);
	ft_verify_end(info, philos);
	ft_destroy_mutexes(info);
	list().free(info->mem);
	return (0);
}

int	ft_create_mutexes(t_info *info)
{
	int	i;

	info->forks = ft_malloc(sizeof(pthread_mutex_t) * info->args[0], info->mem);
	i = -1;
	while (++i < info->args[0])
		if (pthread_mutex_init(&info->forks[i], NULL) != 0)
			return (2);
	info->print = ft_malloc(sizeof(pthread_mutex_t), info->mem);
	if (pthread_mutex_init(&info->print[0], NULL) != 0)
		return (2);
	return (0);
}
