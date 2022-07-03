/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-m <amaria-m@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:36:30 by amaria-m          #+#    #+#             */
/*   Updated: 2022/07/03 12:19:07 by amaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_philo.h>

int	ft_print(t_philo philo, char *msg)
{
	int	i;

	pthread_mutex_lock(philo.print);
	if (!*(philo.dead))
		i = printf("%ld %i %s\n", *(philo.time), philo.id, msg);
	pthread_mutex_unlock(philo.print);
	return (i);
}

static int	ft_err(int err, char *msg)
{
	printf("%s\n", msg);
	return (err);
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
	return (0);
}
