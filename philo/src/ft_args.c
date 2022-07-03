/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-m <amaria-m@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 18:42:58 by amaria-m          #+#    #+#             */
/*   Updated: 2022/07/02 18:02:07 by amaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_philo.h>

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
		if (string().atoi(argv[i]) <= 0)
			return (1);
		args[i - 1] = string().atoi(argv[i]);
	}
	if (argc == 5)
		args[4] = -1;
	return (0);
}
