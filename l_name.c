/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_name.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 17:52:23 by ymarcill          #+#    #+#             */
/*   Updated: 2018/05/16 20:01:53 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#define RD readlink

int		longuest_name(char *av, t_getname get, int a)
{
	t_read		read;
	int			c;
	int			b;

	c = 0;
	b = 1;
	read.ptr = opendir(av);
	get.path = ft_strdup(av);
	get.path = ft_strjoin(get.path, "/");
	while (read.ptr && (read.file = readdir(read.ptr)) && (RD(av, read.tmp,
		255)) == -1)
	{
		get.path2 = ft_strjoinnf(get.path, read.file->d_name);
		lstat(get.path2, &read.buf);
		free(get.path2);
		if (a == 0 && read.file->d_name[0] == '.')
			continue ;
		if ((get.pws = getpwuid(read.buf.st_uid)) != NULL)
			c = ft_strlen(get.pws->pw_name);
		if (c > b)
			b = c;
	}
	free(get.path);
	read.ptr ? closedir(read.ptr) : ft_putstr("");
	return (b);
}

int		longuest_gname(char *av, int a)
{
	t_getname		get;
	t_read			read;
	int				c;
	int				b;

	c = 0;
	b = 1;
	read.ptr = opendir(av);
	while (read.ptr && (read.file = readdir(read.ptr)) && (RD(av, read.tmp,
		255)) == -1)
	{
		lstat(read.file->d_name, &read.buf);
		if (a == 0 && read.file->d_name[0] == '.')
			continue ;
		if ((get.grname = getgrgid(read.buf.st_gid)) != NULL)
			c = ft_strlen(get.grname->gr_name);
		if (c > b)
			b = c;
	}
	if (read.ptr)
		closedir(read.ptr);
	return (b);
}

void	l_gname(char *path2, char *path, char *pat, int a)
{
	t_read		read;
	t_getname	get;
	int			i;
	int			p;

	p = 0;
	read.ptr = opendir(pat);
	read.ptr ? lstat(path2, &read.buf) : lstat(path, &read.buf);
	ft_putstr("  ");
	if ((get.grname = getgrgid(read.buf.st_gid)) != NULL)
	{
		ft_putstr(get.grname->gr_name);
		p = ft_strlen(get.grname->gr_name);
	}
	i = longuest_gname(pat, a);
	while (p++ < i)
		ft_putchar(' ');
	ft_putstr("  ");
	free(path2);
	if (read.ptr)
		closedir(read.ptr);
}

void	l_name(DIR *str, char *av, char *pat, int a)
{
	t_getname	get;
	t_read		read;
	t_param		param;

	str = opendir(pat);
	get.path = ft_strdup(pat);
	if (str && lstat(pat, &read.buf) == 0 && !S_ISLNK(read.buf.st_mode))
		get.path = ft_strjoin(get.path, "/");
	get.path2 = av ? ft_strjoin(get.path, av) : ft_strdup(get.path);
	str ? lstat(get.path2, &read.buf) : lstat(get.path, &read.buf);
	if ((get.pws = getpwuid(read.buf.st_uid)) != NULL)
		ft_putstr(get.pws->pw_name);
	param.l = ft_strlen(get.pws->pw_name);
	if ((get.pws = getpwuid(read.buf.st_uid)) == NULL)
	{
		ft_putnbr(read.buf.st_uid);
		param.l = nbr_size(read.buf.st_uid);
	}
	param.i = longuest_name(pat, get, a);
	while (param.l++ < param.i)
		ft_putchar(' ');
	l_gname(get.path2, get.path, pat, a);
	str ? closedir(str) : ft_putstr("");
	!av ? free(get.path) : ft_putstr("");
}
