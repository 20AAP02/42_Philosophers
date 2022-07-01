/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-m <amaria-m@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 17:58:57 by amaria-m          #+#    #+#             */
/*   Updated: 2022/07/01 20:04:18 by amaria-m         ###   ########.fr       */
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
