/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_o_setenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 15:22:43 by vame              #+#    #+#             */
/*   Updated: 2015/03/06 15:08:07 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

int			sh_o_create_var(char **var, char **val, char **arg)
{
	if (!(*var = ft_strnew(ft_strlen(arg[1]))))
		return (-1);
	if (arg[2] && !(*val = ft_strnew(ft_strlen(arg[2]) + 1)))
		return (-1);
	if (arg[2])
		(*val)[0] = '=';
	if (sh_o_env_quote(var, arg[1]) == 0 ||
			(arg[2] && sh_o_env_quote(val, arg[2]) == 0))
	{
		ft_strdel(var);
		if (*val)
			ft_strdel(val);
		return (0);
	}
	return (1);
}

int			sh_o_add_var(char **arg, char ***envp)
{
	char		*val;
	char		*var;
	size_t		i;

	val = NULL;
	var = NULL;
	if (!arg[1])
		sh_o_env_print(*envp, 0, arg);
	else if (ft_strlen_c(arg[1], &i, '='))
		return (ft_printf("setenv: Syntax Error.\n"));
	else if (arg[1] && arg[2] && arg[3])
		return (ft_printf("setenv: too many arguments.\n"));
	else if (ft_strcmp(arg[1], "PWD"))
	{
		if (sh_o_create_var(&var, &val, arg) == 0)
			return (ft_printf("Unmatched \".\n"));
		if (!var || !(*envp = sh_o_new_envp(envp, var, val)))
			return (-1);
		ft_strdel(&var);
		if (val)
			ft_strdel(&val);
	}
	return (1);
}

char		**sh_o_create_envp(char ***envp, int i, char *tmp)
{
	char		**new;
	int			j;

	j = 0;
	if (!(new = (char **)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	new[i] = NULL;
	new[i - 1] = tmp;
	while ((*envp)[j++])
		if (!(new[j - 1] = ft_strdup((*envp)[j - 1])))
			return (NULL);
	ft_strdel_double(envp);
	return (new);
}

char		**sh_o_new_envp(char ***envp, char *var, char *val)
{
	char		**new;
	char		*tmp;
	size_t		len;
	int			i;

	i = 0;
	tmp = NULL;
	if (val == NULL && !(tmp = ft_strjoin(var, "=")))
		return (NULL);
	else if (!tmp && !(tmp = ft_strjoin(var, val)))
		return (NULL);
	while ((*envp)[i++])
	{
		ft_strlen_c((*envp)[i - 1], &len, '=');
		if (ft_strncmp((*envp)[i - 1], tmp, len) == 0)
		{
			free((*envp)[i - 1]);
			(*envp)[i - 1] = tmp;
			return (*envp);
		}
	}
	if (!(new = sh_o_create_envp(envp, i, tmp)))
		return (NULL);
	return (new);
}

void		sh_o_del_var(char **arg, char ***envp)
{
	int			i;
	int			j;
	size_t		len_1;
	size_t		len_2;

	i = 1;
	while (arg[i])
	{
		j = 0;
		len_1 = ft_strlen(arg[i]);
		while (ft_strcmp(arg[i], "PWD") && (*envp)[j])
		{
			if (ft_strlen_c((*envp)[j], &len_2, '=') && len_1 == len_2 &&
					ft_strncmp((*envp)[j], arg[i], len_1) == 0)
			{
				free((*envp)[j]);
				(*envp)[j] = (*envp)[j + 1];
				while ((*envp)[j++])
					(*envp)[j] = (*envp)[j + 1];
			}
			else
				j++;
		}
		i++;
	}
}
