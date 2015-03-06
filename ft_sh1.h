/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh1.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 10:42:58 by vame              #+#    #+#             */
/*   Updated: 2015/03/06 16:03:51 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SH1_H
# define FT_SH1_H

# include "libft/libft_ext.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <sys/wait.h>
# include <dirent.h>

# define PATH1 "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/opt/X11/bin:"
# define PATH2 "/usr/texbin:/nfs/zfs-student-2/users/2014_paris/vame/.brew/bin"
# define ERR ": Command not found."
# define ERR_ENV ": No such file or directory."

typedef struct	s_data
{
	char		*pwd;
	char		*oldpwd;
	char		*prompt;
}				t_data;

/*
**	fonctions du builtin cd
*/

int				sh_o_cd(char **arg, char ***envp, t_data **data);
int				sh_o_cd_opt(char *arg);
int				sh_o_cdpath(char ***envp, char ***cdpath);
char			*sh_o_dot(char *operand);
int				sh_o_nodotorslash(char ***envp, char *ope, char **cur);
char			*sh_o_del_chars(char **curpath, int i, int j);
char			*sh_o_del_prev(char **curpath, int *i);
void			sh_o_clean_curpath(char **curpath);
char			*sh_o_cd_tilde(char **ope, char ***envp);

/*
**	fonctions du builtin env
*/

int				sh_o_env(char **arg, char ***envp);
void			sh_o_env_print(char **envp, int opt, char **arg);
void			sh_o_del_tmp(char **tmp, char ***arg_tmp, char ***path_tmp);

/*
**	fonctions du builtin unsetenv
*/

void			sh_o_del_var(char **arg, char ***envp);

/*
**	fonctions du builtin setenv
*/

int				sh_o_add_var(char **arg, char ***envp);
int				sh_o_create_var(char **var, char **val, char **arg);
char			**sh_o_create_envp(char ***envp, int i, char *tmp);
int				sh_o_env_quote(char **dst, char *src);

/*
**	fonctions de gestion des variables d'environnement
*/

int				sh_o_path(char **envp, char ***e);
char			**sh_o_envcpy(char **envp, t_data **data, int dft);
char			**sh_o_new_envp(char ***envp, char *var, char *val);
int				sh_o_cpy_var(char ***envp, char **dst, char *var);
char			**sh_o_env_dft(char ***envp);

/*
**	fonctions de t_data
*/

t_data			*sh_o_new_data(char ***envp);
int				sh_o_free_data(t_data **data);

/*
**	fonctions de gestion des builtins
*/

int				sh_o_builtins(char **arg, char ***envp, t_data **data);
int				sh_o_is_builtin(char *arg);
int				sh_o_blt_cptn(char **arg, int i, char ***envp, t_data **data);

/*
**	fonctions algo sh1 et utilitaires
*/

int				sh_o_cmd(char *l, char **env, char ***envp, t_data **data);
int				sh_o_ac(char **env, char *arg, char **line, char *err);
void			sh_o_fork(char *cmd, char **arg, char ***envp);
int				sh_o_clean(char **line);
int				sh_o_exit(char **arg);
int				sh_o_inception(char *arg, char **line);
void			sh_o_signal_cmd(int sig);
void			sh_o_signal_nocmd(int sig);

#endif
