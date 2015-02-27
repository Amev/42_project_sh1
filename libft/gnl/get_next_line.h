/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/14 14:53:46 by vame              #+#    #+#             */
/*   Updated: 2015/02/05 16:04:01 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

# define BUFF_SIZE 10

typedef struct			s_gnl_list
{
	char				*mem;
	int					index_fd;
	int					test;
	struct s_gnl_list	*nxt;
	struct s_gnl_list	*prv;
}						t_gnl_list;

int						get_next_line(int const fd, char **line);

#endif
