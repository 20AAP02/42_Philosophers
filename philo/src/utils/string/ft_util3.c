/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-m <amaria-m@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 19:55:36 by amaria-m          #+#    #+#             */
/*   Updated: 2022/07/01 18:46:25 by amaria-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_str_util.h>

char	*ft_iter(const char *str, char (*f)(char c))
{
	int		i;
	char	*mem;

	if (!str || !*str || !f)
		return ((char *)str);
	mem = malloc(sizeof(char) * (ft_len(str) + 1));
	i = 0;
	while (str && str[i])
	{
		mem[i] = f(str[i]);
		i++;
	}
	mem[i] = 0;
	return (mem);
}

int	ft_is_number(const char *str)
{
	if (!str || !*str)
		return (0);
	while (str && *str)
	{
		if (*str > '9' || *str < '0')
			return (0);
		str++;
	}
	return (1);
}
