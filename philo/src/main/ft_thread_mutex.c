/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread_mutex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-m <amaria-m@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 18:57:31 by amaria-m          #+#    #+#             */
/*   Updated: 2022/07/01 20:27:21 by amaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_philo.h>

pthread_mutex_t	*ft_inisialise_mutexes(int n_forks, t_list *lst)
{
	pthread_mutex_t	*forks;
	int				i;

	if (!n_forks || !lst)
		return (NULL);
	forks = ft_malloc(sizeof(pthread_mutex_t) * n_forks, lst);
	i = -1;
	while (++i < n_forks)
		pthread_mutex_init(&forks[i], NULL);
	return (forks);
}

void	ft_destroy_mutexes(pthread_mutex_t	*forks, int n_forks)
{
	int	i;

	if (!forks || !n_forks)
		return ;
	i = -1;
	while (++i < n_forks)
		pthread_mutex_destroy(&forks[i]);
}

static void	ft_set_philo(t_philo *philo, t_info *info, int i)
{
	philo->number = i + 1;
	philo->n_philos = info->args[0];
	philo->die_t = info->args[1];
	philo->eat_t = info->args[2];
	philo->sleep_t = info->args[3];
	philo->opt = info->args[4];
	philo->time = *(info->time);
}

int	ft_crt_threads(t_info *info, void *(*f)(void *), t_list *mem)
{
	int		i;
	t_philo	*philo;

	if (!info || !info->args[0] || !f || !mem)
		return (0);
	info->philos = ft_malloc(sizeof(pthread_t) * info->args[0], mem);
	if (!info->philos)
		return (0);
	i = -1;
	while (++i < info->args[0])
	{
		philo = ft_malloc(sizeof(t_philo), mem);
		ft_set_philo(philo, info, i);
		if (pthread_create(&(info->philos[i]), NULL, f, philo) != 0)
			return (0);
	}
	i = -1;
	while (++i < info->args[0])
		if (pthread_join(info->philos[i], NULL) != 0)
			return (0);
	return (1);
}
