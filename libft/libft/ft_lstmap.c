/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 13:37:52 by vame              #+#    #+#             */
/*   Updated: 2014/12/09 17:08:04 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*dst;
	t_list	*tmp;
	t_list	*tmp_n;

	if (!(lst && f) || !(dst = ft_lstnew(lst->content, lst->content_size)))
		return (NULL);
	dst = f(dst);
	tmp = dst;
	while (lst->next)
	{
		lst = lst->next;
		if (!(tmp_n = ft_lstnew(lst->content, lst->content_size)))
			return (NULL);
		tmp_n = f(tmp_n);
		tmp->next = tmp_n;
		tmp = tmp->next;
	}
	return (dst);
}
