/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-m <amaria-m@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:36:30 by amaria-m          #+#    #+#             */
/*   Updated: 2022/07/02 21:00:57 by amaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_philo.h>

int	ft_print(t_philo philo, char *msg)
{
	int	i;

	pthread_mutex_lock(philo.print);
	if (!*(philo.dead))
		i = printf("%ld %i %s\n", ft_get_time() - philo.start_t, philo.id, msg);
	pthread_mutex_unlock(philo.print);
	return (i);
}

static int	ft_err(int err, char *msg)
{
	printf("%s\n", msg);
	return (err);
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
		ft_print(*philo, "is thinking");
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_info	info;

	info.mem = list().new(NULL);
	if (ft_get_args(argc, argv, info.args))
		return (ft_err(0, "err: incorrect arguments"));
	if (ft_create_mutexes(&info))
		return (ft_err(0, "err: problem w/ mutexes"));
	if (ft_create_threads(&info))
		return (ft_err(0, "err: problem w/ threads"));
	if (info.dead)
		printf("1\n");
	return (0);
}
