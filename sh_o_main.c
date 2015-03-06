/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_o_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/30 13:22:53 by vame              #+#    #+#             */
/*   Updated: 2015/03/06 15:47:37 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

void		sh_o_signal_cmd(int sig)
{
	if (sig == SIGINT)
		ft_printf("\n");
	if (sig == SIGSEGV)
		ft_printf("Segmentation fault\n");
}

void		sh_o_signal_nocmd(int sig)
{
	char	*pwd;

	if (sig == SIGINT)
		ft_printf("\n");
	if (sig == SIGSEGV)
		ft_printf("Segmentation fault\n");
	if (!(pwd = getcwd(NULL, 0)))
	{
		ft_putstr_fd("malloc error\n", 2);
		exit(-1);
	}
	ft_printf("{cyn}/%s $> {eoc}", ft_strrchr(pwd, '/') + 1);
	free(pwd);
}

int			main(int ac, char **av, char **envp)
{
	int			res;
	char		*line;
	char		**e;
	char		**path;
	t_data		*data;

	(void)av[ac - 1];
	data = NULL;
	if (!(e = sh_o_envcpy(envp, &data, 1)) && ft_putstr_fd("malloc error\n", 2))
		exit(-1);
	ft_printf("{cyn}/%s $> {eoc}", ft_strrchr(data->pwd, '/') + 1);
	while (1)
	{
		signal(SIGINT, sh_o_signal_nocmd);
		if ((res = get_next_line(0, &line)) == 0)
			break ;
		if ((res == -1 || sh_o_path(e, &path) == -1 ||
					(res = sh_o_cmd(line, path, &e, &data)) == -1) &&
				ft_putstr_fd("malloc error\n", 2))
			exit(-1);
		ft_strdel_double(&path);
		ft_strdel(&line);
		ft_printf("{cyn}/%s $> {eoc}", ft_strrchr(data->pwd, '/') + 1);
	}
	return (0);
}
