/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-m <amaria-m@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 15:31:36 by amaria-m          #+#    #+#             */
/*   Updated: 2022/07/05 18:42:12 by amaria-m         ###   ########.fr       */
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

void	ft_set_philos(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->n)
	{
		info->philos[i].id = i + 1;
		info->philos[i].die_t = info->die_t;
		info->philos[i].eat_t = info->eat_t;
		info->philos[i].sleep_t = info->sleep_t;
		info->philos[i].eat_times = 0;
		info->philos[i].forks = info->forks;
		info->philos[i].print = &info->print;
		info->philos[i].mem = info->mem;
		info->philos[i].end_t = info->die_t;
		info->philos[i].start_t = &info->start_t;
		info->philos[i].destroy = &info->destroy;
		info->philos[i].fork_checker = info->fork_checker;
		info->philos[i].left = i;
		info->philos[i].right = ((i + 1) != info->n) * (i + 1);
	}
}

int	ft_info_init(t_info *info, int *args)
{
	int	i;

	info->n = args[0];
	info->die_t = args[1];
	info->eat_t = args[2];
	info->sleep_t = args[3];
	info->eat_times = args[4];
	info->destroy = 0;
	info->forks = ft_malloc(sizeof(pthread_mutex_t) * info->n, info->mem);
	info->threads = ft_malloc(sizeof(pthread_t) * info->n, info->mem);
	info->fork_checker = ft_malloc(sizeof(int) * info->n, info->mem);
	i = -1;
	while (++i < info->n)
		info->fork_checker[i] = 0;
	i = -1;
	while (++i < info->n)
		if (pthread_mutex_init(&info->forks[i], NULL) != 0)
			return (1);
	if (pthread_mutex_init(&info->print, NULL) != 0)
		return (1);
	info->philos = ft_malloc(sizeof(t_philo) * info->n, info->mem);
	ft_set_philos(info);
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
