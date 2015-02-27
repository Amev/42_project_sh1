/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_usgnd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/11 11:06:52 by vame              #+#    #+#             */
/*   Updated: 2015/01/21 11:20:22 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_cte_str(unsigned long long int nb, unsigned int base,
		size_t *len)
{
	size_t					i;
	char					*result;

	i = 0;
	while (nb >= base)
	{
		*len += 1;
		nb /= base;
	}
	if (!(result = (char *)malloc(sizeof(char) * (*len + 1))))
		return (NULL);
	while (i < *len)
		result[i++] = '0';
	result[i] = '\0';
	return (result);
}

static char	*ft_put_good_char(char *result)
{
	int						i;

	i = 0;
	while (result[i++])
		if (result[i - 1] > 57)
			result[i - 1] += 39;
	return (result);
}

char		*ft_itoa_base_u(unsigned long long int nb, unsigned int base)
{
	char					*result;
	size_t					len;
	size_t					i;
	unsigned int			coef;

	i = 0;
	len = 1;
	if (!(result = ft_cte_str(nb, base, &len)))
		return (NULL);
	i = len - 1;
	while (nb >= base)
	{
		coef = nb % base;
		result[i--] = '0' + coef;
		nb /= base;
	}
	result[i] = '0' + nb;
	result = ft_put_good_char(result);
	return (result);
}
