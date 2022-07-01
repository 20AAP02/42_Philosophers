/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-m <amaria-m@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:36:30 by amaria-m          #+#    #+#             */
/*   Updated: 2022/07/01 20:40:27 by amaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_philo.h>

void	*ft_routine(void *ptr)
{
	t_philo			*philo;
	struct timeval	c_time;
	suseconds_t		time;

	philo = ptr;
	gettimeofday(&c_time, NULL);
	time = c_time.tv_usec - philo->time.tv_usec;
	sleep(1);
	printf("thread test %i at %ld\n", philo->number, time);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_info	info;

	(void) argc;
	info.mem = list().new(NULL);
	if (ft_get_args(argc, argv, info.args))
		return (printf("err: args are incorrect\n"));
	if (gettimeofday(info.time, NULL) != 0)
		return (printf("err: time error\n"));
	info.forks = ft_inisialise_mutexes(info.args[0], info.mem);
	if (!info.forks)
		return (printf("err: mutex error\n"));
	if (!ft_crt_threads(&info, ft_routine, info.mem))
		return (printf("err: thread error\n"));
	ft_destroy_mutexes(info.forks, info.args[0]);
	list().free(info.mem);
	return (0);
}
