/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_size2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 18:42:30 by ymarcill          #+#    #+#             */
/*   Updated: 2018/05/16 19:38:12 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		longuest_size(char *av, int a)
{
	t_read		read;
	t_getname	get;
	int			c;
	int			b;

	c = 0;
	b = 1;
	read.ptr = opendir(av);
	get.path2 = ft_strdup(av);
	get.path2 = ft_strjoin(get.path2, "/");
	while (read.ptr && (read.file = readdir(read.ptr)))
	{
		get.path = ft_strjoinnf(get.path2, read.file->d_name);
		lstat(get.path, &read.buf);
		free(get.path);
		if (a == 0 && read.file->d_name[0] == '.')
			continue ;
		c = nbr_size(read.buf.st_size);
		if (c >= b)
			b = c;
	}
	free(get.path2);
	read.ptr ? closedir(read.ptr) : ft_putstr("");
	return (b);
}

void	l_size2_bis(struct stat buf, int i, int lgsts, char *path2)
{
	if (S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode))
	{
		ft_putnbr(major(buf.st_rdev));
		ft_putstr(",  ");
		ft_putnbr(minor(buf.st_rdev));
	}
	else
	{
		i = nbr_size(buf.st_size);
		if (i < lgsts)
		{
			while (i++ < lgsts)
				ft_putchar(' ');
		}
		ft_putnbr(buf.st_size);
	}
	free(path2);
}

void	l_size2(char *av, int lgsts, char *pat, int a)
{
	t_read		read;
	t_getname	get;

	read.ptr = opendir(pat);
	get.path = ft_strdup(pat);
	if (read.ptr && lstat(pat, &read.buf) == 0 && !S_ISLNK(read.buf.st_mode))
		get.path = ft_strjoin(get.path, "/");
	if (av)
		get.path2 = ft_strjoin(get.path, av);
	else
	{
		get.path2 = ft_strdup(get.path);
		free(get.path);
		av = pat;
	}
	if (a == 0 && av[0] == '.')
		return ;
	read.ptr ? lstat(get.path2, &read.buf) : lstat(get.path, &read.buf);
	l_size2_bis(read.buf, get.i, lgsts, get.path2);
	read.ptr ? closedir(read.ptr) : ft_putstr("");
}
