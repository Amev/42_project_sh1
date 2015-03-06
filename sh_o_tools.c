/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_o_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vame <vame@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/30 16:11:08 by vame              #+#    #+#             */
/*   Updated: 2015/03/06 16:14:41 by vame             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

int			sh_o_clean(char **line)
{
	int			i;
	char		*tmp;

	i = 0;
	tmp = NULL;
	while (*line && (*line)[i])
	{
		if ((*line)[i] == 9)
			(*line)[i] = ' ';
		i++;
	}
	i = 1;
	if (!(tmp = ft_strnew(ft_strlen(*line))))
		return (-1);
	i = sh_o_env_quote(&tmp, *line);
	*line = tmp;
	return (i);
}

int			sh_o_env_quote(char **dst, char *src)
{
	int			i;
	int			j;
	int			quote;

	i = 0;
	j = 0;
	quote = 1;
	while ((*dst)[j])
		j++;
	while (src && src[i++])
	{
		if (src[i - 1] == '"')
			quote = quote == 1 ? 0 : 1;
		else
			(*dst)[j++] = src[i - 1];
	}
	return (quote);
}

char		*sh_o_del_chars(char **curpath, int i, int j)
{
	(*curpath)[i] = (*curpath)[i + j];
	while ((*curpath)[i++])
		(*curpath)[i] = (*curpath)[i + j];
	return (*curpath);
}

char		*sh_o_del_prev(char **curpath, int *i)
{
	int			len;
	int			j;

	j = *i - 1;
	len = j - 2 > 0 ? 4 : 3;
	if (j > 0)
	{
		j -= 2;
		while (j > 0 && (*curpath)[j--] != '/')
			len++;
		j++;
	}
	(*curpath)[j] = (*curpath)[j + len];
	while ((*curpath)[j++])
		(*curpath)[j] = (*curpath)[j + len];
	if ((*curpath)[0] == '\0')
	{
		(*curpath)[0] = '/';
		(*curpath)[1] = '\0';
	}
	*i -= *i > (len + 1) ? (len + 1) : (*i - 1);
	return (*curpath);
}

void		sh_o_clean_curpath(char **curpath)
{
	int			i;

	i = 0;
	while (*curpath && (*curpath)[i++])
	{
		if ((*curpath)[i - 1] == '.' && (*curpath)[i] == '.')
			i++;
		else if ((i == 1 || (*curpath)[i - 2] == '/') &&
				(*curpath)[i - 1] == '.' && (*curpath)[i] == '/')
			*curpath = sh_o_del_chars(curpath, i-- - 1, 2);
	}
	i = 0;
	while (*curpath && (*curpath)[i++])
		if ((i == 1 || (*curpath)[i - 2] == '/') && (*curpath)[i - 1] ==
				'.' && (*curpath)[i] == '.' && ((*curpath)[i + 1] == '/' ||
					(*curpath)[i + 1] == '\0'))
			*curpath = sh_o_del_prev(curpath, &i);
	i = 0;
	while (*curpath && (*curpath)[i++])
		if ((*curpath)[i - 1] == '/' && (*curpath)[i] == '/')
			*curpath = sh_o_del_chars(curpath, i-- - 1, 1);
	if ((i = ft_strlen(*curpath)) > 1)
		if ((*curpath)[i - 1] == '/')
			(*curpath)[i - 1] = '\0';
}
