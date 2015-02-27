/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_o_cd_algo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/06 12:21:35 by vame              #+#    #+#             */
/*   Updated: 2015/02/09 12:54:06 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

static int		sh_o_cd_cdpath(char ***envp, t_data **data)
{
	int			res;
	char		*tmp;

	if ((res = sh_o_cpy_var(envp, &tmp, "OLDPWD=")) == -1)
		return (-1);
	if (res == 2)
		return (ft_printf("cd: OLDPWD not set\n"));
	else
	{
		ft_strdel(&tmp);
		chdir((*data)->oldpwd);
		tmp = (*data)->pwd;
		(*data)->pwd = (*data)->oldpwd;
		(*data)->oldpwd = tmp;
		ft_printf("%s\n", (*data)->pwd);
		return (3);
	}
}

static int		sh_o_cdcur(int opt, char **ope, char ***envp)
{
	int			res;
	char		*cur;

	res = 0;
	cur = NULL;
	if ((*ope)[0] == '~')
		if (!(*ope = sh_o_cd_tilde(ope, envp)))
			return (-1);
	if ((*ope)[0] == '/')
		if (!(cur = ft_strdup(*ope)))
			return (-1);
	if ((*ope)[0] == '.')
		if (!(cur = sh_o_dot(*ope)))
			return (-1);
	if ((*ope)[0] != '/' && (*ope)[0] != '.' && (*ope)[0] != '\0')
		if ((res = sh_o_nodotorslash(envp, *ope, &cur)) == -1)
			return (-1);
	ft_strdel(ope);
	if (opt == 0 || opt == -1)
		sh_o_clean_curpath(&cur);
	if ((opt == 0 || opt == -1) && (cur == NULL || cur[0] == '\0'))
		return (3);
	*ope = cur;
	return (1);
}

static int		sh_o_chdir(char **curpath, char ***envp, t_data **data, int opt)
{
	if (chdir(*curpath) == -1)
		return (-2);
	if (opt == 0 || opt == -1)
		if (!(*envp = sh_o_new_envp(envp, "PWD=", *curpath)))
			return (-1);
	if (opt == 1)
	{
		ft_strdel(curpath);
		if (!(*curpath = getcwd(NULL, 0)))
			return (-1);
		if (!(*envp = sh_o_new_envp(envp, "PWD=", *curpath)))
			return (-1);
	}
	ft_strdel(&(*data)->oldpwd);
	(*data)->oldpwd = (*data)->pwd;
	(*data)->pwd = *curpath;
	return (3);
}

int				sh_o_cd(char **arg, char ***envp, t_data **data)
{
	int			i;
	int			opt;
	int			res;
	char		*ope;

	i = 1;
	res = 0;
	ope = NULL;
	if (arg[i] == NULL || ft_strcmp(arg[i], "~") == 0)
		res = sh_o_cpy_var(envp, &ope, "HOME=");
	if (!(opt = 0) && res == 2)
		return (ft_printf("cd: HOME not set\n"));
	if (arg[i] && ft_strcmp(arg[i], "-") == 0)
		return (sh_o_cd_cdpath(envp, data));
	if (arg[i] && arg[i][0] == '-' && (opt = sh_o_cd_opt(arg[i] + 1)) != -1)
		i++;
	if (arg[i] && arg[i + 1])
		return (ft_printf("cd: too many arguments.\n"));
	if (res == 0 && !(ope = ft_strdup(arg[i])))
		return (-1);
	if ((res = sh_o_cdcur(opt, &ope, envp)) == -1 || res == 3)
		return (res);
	else if ((res = sh_o_chdir(&ope, envp, data, opt)) == -2)
		return (ft_printf("cd: no such file or directory: %s\n", arg[i]));
	return (res);
}
