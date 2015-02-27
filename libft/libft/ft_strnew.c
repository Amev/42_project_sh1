/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 15:51:16 by vame              #+#    #+#             */
/*   Updated: 2014/12/09 11:14:27 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*dst;
	size_t	i;

	i = 0;
	if (!(dst = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (i <= size)
		dst[i++] = '\0';
	return (dst);
}
