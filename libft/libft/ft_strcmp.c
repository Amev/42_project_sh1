/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 16:48:08 by vame              #+#    #+#             */
/*   Updated: 2014/11/14 16:40:48 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*tmp1;
	unsigned char	*tmp2;

	tmp1 = (unsigned char *)s1;
	tmp2 = (unsigned char *)s2;
	if (!(tmp1 && tmp2))
		return (0);
	if (!tmp1)
		return (-(*tmp2));
	if (!tmp2)
		return (*tmp1);
	while (*tmp1 == *tmp2 && *tmp1 != '\0' && *tmp2 != '\0')
	{
		tmp1++;
		tmp2++;
	}
	return (*tmp1 - *tmp2);
}
