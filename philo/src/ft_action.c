/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-m <amaria-m@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 18:11:41 by amaria-m          #+#    #+#             */
/*   Updated: 2022/07/06 13:51:58 by amaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_philo.h>

void	ft_sleep(t_philo *philo, long long time)
{
	long long	start;

	start = ft_get_time();
	while (!*(philo->destroy) && ft_get_time() < start + time)
		usleep(10);
}

void	ft_eat(t_philo *philo)
{
	int	i;

	i = 0;
	while (!i && !*(philo->destroy))
	{
		if (!(philo->fork_checker[philo->left]))
		{
			philo->fork_checker[philo->left] = 1;
			pthread_mutex_lock(&philo->forks[philo->left]);
			if (!(philo->fork_checker[philo->right]))
			{
				philo->fork_checker[philo->right] = ++i;
				pthread_mutex_lock(&philo->forks[philo->right]);
				ft_print(philo, "has a fork 🍴");
				ft_print(philo, "has a fork 🍴");
				ft_print(philo, "is eating 🍝");
				philo->end_t += philo->die_t;
				ft_sleep(philo, (long long)philo->eat_t);
				pthread_mutex_unlock(&philo->forks[philo->right]);
				philo->fork_checker[philo->right] = 0;
			}
			pthread_mutex_unlock(&philo->forks[philo->left]);
			philo->fork_checker[philo->left] = 0;
		}
	}
}
