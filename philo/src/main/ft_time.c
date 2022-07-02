/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-m <amaria-m@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 17:20:25 by amaria-m          #+#    #+#             */
/*   Updated: 2022/07/02 19:15:12 by amaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_philo.h>

suseconds_t	ft_get_time(void)
{
	struct timeval	c_time;

	gettimeofday(&c_time, NULL);
	return (c_time.tv_usec);
}

void	ft_sleep(t_info *info, suseconds_t waitime)
{
	suseconds_t	start;
	suseconds_t	now;

	start = ft_get_time();
	while (!info->dead)
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
			if (ft_get_time() >= philos[i].end_t)
			{
				ft_print(philos[i], "died");
				info->dead = 1;
			}
		}
	}
	return (0);
}
