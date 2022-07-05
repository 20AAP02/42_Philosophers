/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-m <amaria-m@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 15:31:36 by amaria-m          #+#    #+#             */
/*   Updated: 2022/07/05 15:32:47 by amaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_philo.h>


void	*ft_malloc(size_t size, t_list *lst)
{
	void	*ptr;

	ptr = malloc(size);
	lst = list().add(lst, ptr);
	return (ptr);
}

int	ft_get_args(int argc, char **argv, int *args)
{
	int	i;

	if (!argv || (argc != 5 && argc != 6))
		return (1);
	i = 0;
	while (++i < argc)
	{
		if (!argv[i])
			return (1);
		if (!string().is_num(argv[i]))
			return (1);
		args[i - 1] = string().atoi(argv[i]);
	}
	if (argc == 5)
		args[4] = -1;
	if (args[0] <= 0 || (args[4] <= 0 && argc == 6))
		return (1);
	return (0);
}

int	ft_info_init(t_info *info, int *args)
{
	int	i;

	info->n = args[0];
	info->die_t = args[1];
	info->eat_t = args[2];
	info->sleep_t = args[3];
	info->eat_times = args[4];
	info->forks = ft_malloc(sizeof(pthread_mutex_t) * info->n, info->mem);
	info->philos = ft_malloc(sizeof(pthread_t) * info->n, info->mem);
	i = -1;
	while (++i < info->n)
		if (pthread_mutex_init(&info->forks[i], NULL) != 0)
			return (1);
	if (pthread_mutex_init(&info->print, NULL) != 0)
		return (1);
	return (0);
}

int	ft_mutex_destroy(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->n)
		if (pthread_mutex_destroy(&info->forks[i]) != 0)
			return (1);
	if (pthread_mutex_destroy(&info->print) != 0)
		return (1);
	return (0);
}

int	ft_threads_init(t_info *info, int *args)
{
	if (ft_info_init(info, args))
		return (1);
	if (ft_mutex_destroy(info))
		return (1);
	return (0);
}
