/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-m <amaria-m@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:36:30 by amaria-m          #+#    #+#             */
/*   Updated: 2022/07/05 15:33:42 by amaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_philo.h>

int	main(int argc, char **argv)
{
	t_info	info;
	int		args[5];

	info.mem = list().new(NULL);
	if (ft_get_args(argc, argv, args))
		return (printf("err: invalid arguments\n"));
	if (ft_threads_init(&info, args))
		return (printf("err: problem iniciating\n"));
	list().free(info.mem);
	return (0);
}
