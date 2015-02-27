/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_o_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/30 13:22:53 by vame              #+#    #+#             */
/*   Updated: 2015/02/09 12:54:04 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

int			main(int ac, char **av, char **envp)
{
	int			res;
	char		*line;
	char		**env;
	char		**path;
	t_data		*data;

	(void)av[ac - 1];
	data = NULL;
	if (!(env = sh_o_envcpy(envp, &data)) && ft_putstr_fd("malloc error\n", 2))
		exit(-1);
	ft_printf("{cyn}/%s $> {eoc}", ft_strrchr(data->pwd, '/') + 1);
	while (1)
	{
		if ((res = get_next_line(0, &line)) == 0)
			break ;
		if ((res == -1 || sh_o_path(env, &path) == -1 ||
					(res = sh_o_cmd(line, path, &env, &data)) == -1) &&
				ft_putstr_fd("malloc error\n", 2))
			exit(-1);
		ft_strdel_double(&path);
		ft_strdel(&line);
		ft_printf("{cyn}/%s $> {eoc}", ft_strrchr(data->pwd, '/') + 1);
	}
	return (0);
}
