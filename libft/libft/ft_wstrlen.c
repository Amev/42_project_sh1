/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 15:53:55 by vame              #+#    #+#             */
/*   Updated: 2015/01/20 11:11:31 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_wstrlen(wchar_t *str)
{
	int					i;
	int					len;
	unsigned long int	tmp;

	i = 0;
	len = 0;
	while (str && str[i])
	{
		tmp = (unsigned long int)str[i++];
		if (tmp <= 0x7F)
			len++;
		else if (tmp > 0x10FFFF)
			return (-1);
		else
			while (tmp && ++len > 0)
				tmp = tmp >> 6;
	}
	return (len);
}
