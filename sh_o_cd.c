/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_o_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 10:37:04 by vame              #+#    #+#             */
/*   Updated: 2015/02/09 11:41:32 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

int			sh_o_cd_opt(char *arg)
{
	int			opt;

	opt = 0;
	while (*arg)
	{
		if (*arg == 'L')
			opt = 0;
		else if (*arg == 'P')
			opt = 1;
		else
			return (-1);
		arg++;
	}
	return (opt);
}

char		*sh_o_cd_tilde(char **ope, char ***envp)
{
	char		*tmp;
	char		*slash;

	tmp = NULL;
	if (sh_o_cpy_var(envp, &tmp, "HOME=") == 1)
	{
		if (!(slash = ft_strnew(ft_strlen(tmp) + ft_strlen(*ope) + 1)))
			return (NULL);
		slash = ft_strcat(ft_strcat(ft_strcat(slash, tmp), "/"), *ope);
		ft_strdel(ope);
		ft_strdel(&tmp);
		*ope = slash;
	}
	else
		*ope = ft_strcpy(*ope, *ope + 1);
	return (*ope);
}

char		*sh_o_dot(char *operand)
{
	char		*pwd;
	char		*curpath;

	pwd = NULL;
	if (!(pwd = getcwd(NULL, 0)))
		return (NULL);
	if (!(curpath = ft_strnew(ft_strlen(pwd) + ft_strlen(operand) + 1)))
		return (NULL);
	curpath = ft_strcat(ft_strcat(ft_strcat(curpath, pwd), "/"), operand);
	ft_strdel(&pwd);
	return (curpath);
}

int			sh_o_nodotorslash(char ***envp, char *ope, char **cur)
{
	int			i;
	int			res;
	char		**cdpath;

	i = 0;
	if ((res = sh_o_cdpath(envp, &cdpath)) == -1)
		return (-1);
	if (!(*cur = sh_o_dot(ope)))
		return (-1);
	if (!(access(*cur, F_OK)))
		return (1);
	ft_strdel(cur);
	while (res == 1 && cdpath[i++])
	{
		if (!(*cur = ft_strnew(ft_strlen(cdpath[i - 1]) + ft_strlen(ope) + 1)))
			return (-1);
		*cur = ft_strcat(ft_strcat(ft_strcat(*cur, cdpath[i - 1]), "/"), ope);
		if (!(access(*cur, F_OK)))
			return (1);
		ft_strdel(cur);
	}
	if (!(*cur = sh_o_dot(ope)))
		return (-1);
	return (0);
}
