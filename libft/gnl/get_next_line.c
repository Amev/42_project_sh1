/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/25 12:19:19 by vame              #+#    #+#             */
/*   Updated: 2015/02/01 11:59:57 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_gnl_list	*gnl_createnew(int fd, t_gnl_list **fd_list)
{
	t_gnl_list			*new;

	if (fd < 0 || !(new = (t_gnl_list *)malloc(sizeof(t_gnl_list))))
		return (NULL);
	if (!(new->mem = ft_strnew(BUFF_SIZE)))
		return (NULL);
	new->nxt = NULL;
	new->prv = NULL;
	new->index_fd = fd;
	new->test = 0;
	if (!(*fd_list))
		*fd_list = new;
	else
	{
		new->prv = *fd_list;
		(*fd_list)->nxt = new;
	}
	return (new);
}

t_gnl_list	*gnl_memlist(int fd, t_gnl_list **fd_list)
{
	if (*fd_list && (*fd_list)->index_fd == fd)
		return (*fd_list);
	while (*fd_list && ((*fd_list)->prv != NULL))
		*fd_list = (*fd_list)->prv;
	while (*fd_list)
	{
		if ((*fd_list)->index_fd == fd)
			return (*fd_list);
		if ((*fd_list)->nxt == NULL)
			break ;
		*fd_list = (*fd_list)->nxt;
	}
	return (gnl_createnew(fd, fd_list));
}

int			gnl_write(t_list **l, char **line, int res)
{
	char				*str;
	t_list				*tmp;
	size_t				i;
	size_t				j;

	i = 0;
	if (!(str = ft_strnew(BUFF_SIZE)))
		return (-1);
	while (*l && !(j = 0))
	{
		str = ft_strncpy(str, (char *)(*l)->content, BUFF_SIZE);
		while (str[j] && str[j] != '\n')
			(*line)[i++] = str[j++];
		tmp = *l;
		*l = (*l)->next;
		free(tmp->content);
		free(tmp);
		if (str[j] == '\n')
		{
			free(str);
			return (1);
		}
	}
	free(str);
	return (res);
}

int			gnl_read(t_list **list, int fd, size_t *len, t_gnl_list **f_l)
{
	int					ret;
	t_list				*tmp;
	size_t				i;

	i = 0;
	if ((*f_l)->mem[0] || ((*f_l)->test == 1 && *list))
		return (1);
	while ((ret = read(fd, (*f_l)->mem, BUFF_SIZE)))
	{
		i = 0;
		if (ret == -1 || !(tmp = ft_lstnew((*f_l)->mem, ret)))
			return (-1);
		ft_lstadd_back(list, tmp);
		while ((*f_l)->mem[i] && (*f_l)->mem[i] != '\n' && ++(*len) > 0)
			i++;
		if ((*f_l)->mem[i++] == '\n')
		{
			(*f_l)->mem = ft_strncpy((*f_l)->mem, (*f_l)->mem + i, BUFF_SIZE);
			return (1);
		}
		ft_bzero((*f_l)->mem, BUFF_SIZE);
	}
	return (i == 0 ? 0 : 1);
}

int			get_next_line(int const fd, char **line)
{
	static t_gnl_list	*f_l;
	t_list				*list;
	size_t				len;
	int					i;

	i = 0;
	len = 0;
	list = NULL;
	if (BUFF_SIZE <= 0 || !(f_l = gnl_memlist(fd, &f_l)))
		return (-1);
	if (f_l->mem && f_l->mem[i] && !(f_l->test = 0))
	{
		if (!(list = ft_lstnew(f_l->mem, ft_strlen(f_l->mem))))
			return (-1);
		while (f_l->mem[i] && f_l->mem[i] != '\n' && ++len > 0)
			i++;
		if (i == 0 && f_l->mem[i] == '\n' && f_l->mem[i + 1] == '\0')
			f_l->test = 1;
		if (f_l->mem[i] == '\n')
			i++;
		f_l->mem = ft_strncpy(f_l->mem, f_l->mem + i, BUFF_SIZE);
	}
	if ((i = gnl_read(&list, fd, &len, &f_l)) == -1)
		return (-1);
	return (!(*line = ft_strnew(len)) ? -1 : gnl_write(&list, line, i));
}
