/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_o_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/30 16:16:06 by vame              #+#    #+#             */
/*   Updated: 2015/02/06 16:58:43 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

int			sh_o_is_builtin(char *arg)
{
	if (ft_strcmp(arg, "setenv") == 0)
		return (1);
	else if (ft_strcmp(arg, "unsetenv") == 0)
		return (2);
	else if (ft_strcmp(arg, "cd") == 0)
		return (3);
	else if (ft_strcmp(arg, "env") == 0)
		return (4);
	return (0);
}

int			sh_o_builtins(char **arg, char ***envp, t_data **data)
{
	int			builtins;

	builtins = sh_o_is_builtin((arg)[0]);
	if (builtins == 1)
		return (sh_o_add_var(arg, envp));
	if (builtins == 2)
		sh_o_del_var(arg, envp);
	if (builtins == 3)
		return (sh_o_cd(arg, envp, data));
	if (builtins == 4)
		return (sh_o_env(arg, envp));
	return (builtins);
}
