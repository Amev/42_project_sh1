/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 13:11:15 by vame              #+#    #+#             */
/*   Updated: 2015/02/07 13:00:04 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static const char	*ft_clean(const char *str, int *sign)
{
	while (*str == ' ' || *str == '\n' || *str == '\v' || *str == '\t' ||
			*str == '\r' || *str == '\f')
		str++;
	if (*str == '-')
	{
		*sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	return (str);
}

int					ft_atoi(const char *str)
{
	long long int	res;
	long long int	tmp;
	int				sign;

	res = 0;
	sign = 1;
	str = ft_clean(str, &sign);
	while (*str && ft_isdigit(*str) == 1)
	{
		tmp = res;
		res = res * 10 + sign * (*str++ - '0');
		if (tmp > 0 && res <= tmp)
			return (-1);
		else if (tmp < 0 && res >= tmp)
			return (0);
	}
	return ((int)res);
}
