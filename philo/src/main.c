/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-m <amaria-m@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:36:30 by amaria-m          #+#    #+#             */
/*   Updated: 2022/07/05 15:36:12 by amaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_philo.h>

int	ft_error(char *msg)
{
	write(2, msg, string().len(msg));
	return (1);
}

int	main(int argc, char **argv)
{
	t_info	info;
	int		args[5];

	info.mem = list().new(NULL);
	if (ft_get_args(argc, argv, args))
		return (ft_error("err: invalid arguments\n"));
	if (ft_threads_init(&info, args))
		return (ft_error("err: problem initiating threads\n"));
	list().free(info.mem);
	return (0);
}
