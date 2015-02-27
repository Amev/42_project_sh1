/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_o_env_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/06 14:02:37 by vame              #+#    #+#             */
/*   Updated: 2015/02/07 16:09:59 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

static int	sh_o_env_opt(char **arg, int *i)
{
	int			j;
	int			opt;

	opt = 0;
	if (arg[*i] && arg[*i][0] == '-')
	{
		j = 1;
		opt = 1;
		while (arg[*i][j])
		{
			if (arg[*i][j] != 'i')
			{
				ft_printf("env: illegal option -- %c\nusage env ", arg[*i][j]);
				ft_printf("[-i] [name=value ...] [utility [argument ...]]\n");
				return (-1);
			}
			j++;
		}
		*i += 1;
	}
	return (opt);
}

static int	sh_o_env_add_tmp_var(char ***envp, int *i, char **arg)
{
	size_t		len;
	char		*var;

	while (arg[*i] && arg[*i][0] != '=' && ft_strlen_c(arg[*i], &len, '=') == 1)
	{
		if (!(var = ft_strnew(len)))
			return (-1);
		var = ft_strncpy(var, arg[*i], len);
		if (!(*envp = sh_o_new_envp(envp, var, arg[*i] + len)))
			return (-1);
		ft_strdel(&var);
		*i += 1;
	}
	return (1);
}

void		sh_o_env_print(char **envp, int opt, char **arg)
{
	int			i;

	i = 0;
	if (opt == 0)
		while (envp[i++])
			ft_printf("%s\n", envp[i - 1]);
	i = 2;
	if (opt == 1)
		while (arg[i++])
			ft_printf("%s\n", arg[i - 1]);
}

static int	sh_o_env_cmd(char **envp, char **arg, int i)
{
	int			j;
	int			k;
	char		*tmp;
	char		**arg_tmp;
	char		**path_tmp;

	j = i;
	while ((k = i) && arg[j])
		j++;
	if (!(arg_tmp = (char **)malloc(sizeof(char *) * (j - i + 1))))
		return (-1);
	arg_tmp[j - i] = NULL;
	j = 0;
	while (arg[i])
		if (!(arg_tmp[j++] = ft_strdup(arg[i++])))
			return (-1);
	if (sh_o_path(envp, &path_tmp) == -1 ||
			(j = sh_o_ac(path_tmp, arg[k], &tmp, ERR_ENV)) == -1)
		return (-1);
	if (j)
		sh_o_fork(tmp, arg_tmp, &envp);
	ft_strdel(&tmp);
	ft_strdel_double(&arg_tmp);
	ft_strdel_double(&path_tmp);
	return (1);
}

int			sh_o_env(char **arg, char ***envp)
{
	int			i;
	int			opt;
	char		**env_tmp;
	t_data		*data_tmp;

	i = 1;
	opt = 0;
	if ((opt = sh_o_env_opt(arg, &i)) == 1)
		if (!(env_tmp = sh_o_envcpy(NULL, &data_tmp)))
			return (-1);
	if (opt == -1)
		return (4);
	if (opt == 0)
		if (!(env_tmp = sh_o_envcpy(*envp, &data_tmp)))
			return (-1);
	if (arg[i] && sh_o_env_add_tmp_var(&env_tmp, &i, arg) == -1)
		return (-1);
	if (arg[i] == NULL)
		sh_o_env_print(env_tmp, opt, arg);
	else if (!(sh_o_is_builtin(arg[i])) && sh_o_env_cmd(env_tmp, arg, i) == -1)
		return (-1);
	ft_strdel_double(&env_tmp);
	sh_o_free_data(&data_tmp);
	return (4);
}
