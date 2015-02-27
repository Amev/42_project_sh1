/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/12 16:30:20 by vame              #+#    #+#             */
/*   Updated: 2015/01/23 11:19:33 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <stdarg.h>
# include <stdio.h>
# include <wchar.h>

typedef struct	s_flags
{
	char		htg;
	char		zero;
	char		plus;
	char		minus;
	char		space;
	char		l;
	char		ll;
	char		h;
	char		hh;
	char		j;
	char		z;
	int			field;
	int			precision;
}				t_flags;

int				ptf_int(char tag, va_list arg, t_flags **f);
int				ptf_str(char *str, t_flags **flags, char tag);
int				ptf_nb_with_base(char tag, va_list arg, t_flags **flags);
int				ptf_check_tag(char tag, va_list arg, t_flags **flags);
int				ft_printf(const char *format, ...);
char			*ptf_toupper(char **str);
unsigned int	ptf_choose_base(char tag);
char			*ptf_cnv(unsigned int base, va_list arg, char tag, t_flags **f);
t_flags			*ptf_flags_init(t_flags **flags);
int				ptf_put_flags(char *f_str, t_flags **flags, va_list arg);
int				ptf_put_int_flags(char *f, int *i, t_flags **flags);
void			ptf_put_easy_flags(char flag, t_flags **flags);
t_flags			*ptf_check_flags(t_flags **flags, const char **f, va_list arg);
int				ptf_is_conversion(char c);
int				ptf_is_flag(char c);
int				ptf_no_conversion(char c, t_flags **flags);
char			*ptf_conv_nb(va_list arg, char tag, t_flags **f);
char			*ptf_precision(char *res, t_flags **f);
int				ptf_print_wstr(wchar_t *str, t_flags **flags);
int				ptf_print_wchar(wchar_t c, t_flags **flags);
char			*ptf_print_sign(char **nb);
char			*ptf_print_0x(char **str, char tag, t_flags **flags);
char			*ptf_strncpy(char *dst, char *src, size_t n);
void			ptf_htg_preci(char *res, char tag, t_flags **f);
wchar_t			*ptf_wstr_preci(wchar_t *str, t_flags **flags, int *len);
void			ptf_asterisk(va_list arg, t_flags **flags, int i);
int				ptf_put_color(const char **format);
void			ptf_print_color(int color);
int				ptf_search_color(const char *str);

#endif
