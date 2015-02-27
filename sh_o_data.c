/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_o_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/05 14:25:54 by vame              #+#    #+#             */
/*   Updated: 2015/02/06 16:53:02 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

t_data		*sh_o_new_data(char ***envp)
{
	int			res;
	t_data		*new;

	if (!(new = (t_data *)malloc(sizeof(new))))
		return (NULL);
	if (!(new->pwd = getcwd(NULL, 0)))
		return (NULL);
	if (!(*envp = sh_o_new_envp(envp, "PWD=", new->pwd)))
		return (NULL);
	if ((res = sh_o_cpy_var(envp, &new->oldpwd, "OLDPWD=")) == -1)
		return (NULL);
	if (res != 1 || access(new->oldpwd, F_OK))
	{
		if (!(new->oldpwd = ft_strdup(new->pwd)))
			return (NULL);
		if (!(*envp = sh_o_new_envp(envp, "OLDPWD=", new->oldpwd)))
			return (NULL);
	}
	return (new);
}

int			sh_o_free_data(t_data **data)
{
	if ((*data)->pwd)
		ft_strdel(&(*data)->pwd);
	if ((*data)->oldpwd)
		ft_strdel(&(*data)->oldpwd);
	free(*data);
	return (1);
}
