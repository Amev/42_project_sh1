/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_o_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/30 13:56:20 by vame              #+#    #+#             */
/*   Updated: 2015/03/06 15:43:02 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

int			sh_o_ac(char **env, char *arg, char **line, char *err)
{
	int			i;
	char		*tmp;
	char		*cmd;

	if ((i = sh_o_inception(arg, line)) == 1)
		return (1);
	cmd = NULL;
	if (!(cmd = ft_strjoin("/", arg)))
		return (-1);
	while (env && env[i])
	{
		if (!(tmp = ft_strjoin(env[i++], cmd)))
			return (-1);
		if (!(access(tmp, X_OK)))
		{
			*line = tmp;
			ft_strdel(&cmd);
			return (1);
		}
		ft_strdel(&tmp);
	}
	ft_printf("%s%s\n", arg, err);
	ft_strdel(&cmd);
	return (0);
}

int			sh_o_inception(char *arg, char **line)
{
	if (arg[0] == '.' || arg[0] == '/')
	{
		if (!(access(arg, X_OK)))
		{
			if (!(*line = ft_strdup(arg)))
			{
				ft_putstr_fd("malloc error\n", 2);
				exit(-1);
			}
			return (1);
		}
	}
	return (0);
}

void		sh_o_fork(char *cmd, char **arg, char ***envp)
{
	pid_t		son;
	int			status;

	signal(SIGINT, sh_o_signal_cmd);
	if ((son = fork()) == -1 && ft_putstr_fd("fork error\n", 2))
		exit(-2);
	if (son > 0)
		wait(&status);
	if (son == 0)
	{
		signal(SIGSEGV, sh_o_signal_cmd);
		if (execve(cmd, arg, *envp) == -1)
			ft_printf("This not a binary file\n");
		exit(0);
	}
}

int			sh_o_exit(char **arg)
{
	int			i;

	if (!arg[1])
		exit(0);
	if (arg[1] && arg[2])
		return (ft_printf("exit: too many arguments.\n"));
	i = 0;
	while (arg[1][i])
		if (ft_isdigit(arg[1][i++]) == 0)
			return (ft_printf("exit: Bad Syntax.\n"));
	exit(ft_atoi(arg[1]));
	return (1);
}

int			sh_o_cmd(char *l, char **env, char ***envp, t_data **data)
{
	char		**ar;
	int			blt;
	int			res;

	if ((res = sh_o_clean(&l)) == -1)
		return (-1);
	if (res == 0)
		return (ft_printf("Unmatched \".\n"));
	if (!(ar = ft_strsplit_esc(l, ' ')))
		return (-1);
	ft_strdel(&l);
	if (ar[0] && ft_strcmp(ar[0], "exit") == 0)
		return (sh_o_exit(ar));
	if (ar[0] && (blt = sh_o_builtins(ar, envp, data)) == -1)
		return (-1);
	if (ar[0] && !blt && (res = sh_o_ac(env, ar[0], &l, ERR)) == -1)
		return (-1);
	if (ar[0] && !blt && res)
		sh_o_fork(l, ar, envp);
	ft_strdel_double(&ar);
	return (1);
}
