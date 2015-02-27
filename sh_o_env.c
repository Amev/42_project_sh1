/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_o_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/30 16:06:13 by vame              #+#    #+#             */
/*   Updated: 2015/02/09 10:26:15 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

int			sh_o_path(char **envp, char ***e)
{
	int			i;

	i = 0;
	*e = NULL;
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
		{
			if (!(*e = ft_strsplit(envp[i] + 5, ':')))
				return (-1);
			return (1);
		}
		i++;
	}
	return (0);
}

int			sh_o_cpy_var(char ***envp, char **dst, char *var)
{
	int			i;
	size_t		len;

	i = 0;
	*dst = NULL;
	len = ft_strlen(var);
	while ((*envp)[i])
	{
		if (ft_strcmp(var, (*envp)[i]) == 0)
			return (0);
		else if (ft_strncmp(var, (*envp)[i], len) == 0)
		{
			if (!(*dst = ft_strdup((*envp)[i] + len)))
			{
				ft_putstr_fd("malloc error\n", 2);
				exit(-1);
			}
			return (1);
		}
		i++;
	}
	return (2);
}

int			sh_o_cdpath(char ***envp, char ***cdpath)
{
	int			i;

	i = 0;
	*cdpath = NULL;
	while ((*envp)[i])
	{
		if (ft_strncmp("CDPATH=", (*envp)[i], 7) == 0)
		{
			if (!(*cdpath = ft_strsplit((*envp)[i] + 7, ':')))
				return (-1);
			return (1);
		}
		i++;
	}
	return (2);
}

char		**sh_o_env_dft(char ***envp)
{
	char		*str;
	char		*tmp;
	int			res;

	if ((res = sh_o_cpy_var(envp, &str, "PATH=")) == -1)
		return (NULL);
	if (res == 2 || res == 0)
	{
		if (!(tmp = ft_strjoin(PATH1, PATH2)))
			return (NULL);
		if (!(*envp = sh_o_new_envp(envp, "PATH=", tmp)))
			return (NULL);
		ft_strdel(&tmp);
	}
	if (res == 1)
		ft_strdel(&str);
	return (*envp);
}

char		**sh_o_envcpy(char **envp, t_data **data)
{
	char		**new;
	int			i;

	i = 0;
	while (envp && envp[i])
		i++;
	if (!(new = (char **)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	new[i] = NULL;
	i = 0;
	while (envp && envp[i++])
	{
		if (!(new[i - 1] = ft_strdup(envp[i - 1])))
			return (NULL);
	}
	if (!(*data = sh_o_new_data(&new)))
		return (NULL);
	if (!(new = sh_o_env_dft(&new)))
		return (NULL);
	return (new);
}
