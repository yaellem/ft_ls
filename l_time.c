/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_time.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 01:44:18 by ymarcill          #+#    #+#             */
/*   Updated: 2018/05/24 23:29:57 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	*ft_link(char *av, DIR *ptr, int l)
{
	t_read	r;

	if (l && (readlink(av, r.tmp, 255)) != -1)
	{
		ptr ? closedir(ptr) : ft_putstr("");
		ptr = NULL;
	}
	return (ptr);
}

void	l_time_date(struct stat buf, int i, char *path3)
{
	if ((time(NULL) - buf.st_mtime) <= 15552000)
	{
		path3 = (ctime(&buf.st_mtime));
		while (i < ft_strlen(path3) - 9)
			ft_putchar(path3[i++]);
	}
	else
	{
		path3 = (ctime(&buf.st_mtime));
		while (i < ft_strlen(path3) - 14)
			ft_putchar(path3[i++]);
		i = ft_strlen(path3) - 6;
		while (i < ft_strlen(path3) - 1)
			ft_putchar(path3[i++]);
	}
}

void	l_time(DIR *str, char *av, char *pat)
{
	t_read		read;
	t_getname	get;

	str = opendir(pat);
	get.path = ft_strdup(pat);
	if (str && lstat(pat, &read.buf) == 0 && !S_ISLNK(read.buf.st_mode))
		get.path = ft_strjoin(get.path, "/");
	get.path2 = av ? ft_strjoin(get.path, av) : ft_strdup(get.path);
	read.ptr = opendir(get.path2);
	get.i = 3;
	str ? lstat(get.path2, &read.buf) : lstat(get.path, &read.buf);
	l_time_date(read.buf, get.i, get.path3);
	ft_putchar(' ');
	free(get.path2);
	if (str)
		closedir(str);
	if (read.ptr)
		closedir(read.ptr);
	!av ? free(get.path) : ft_putstr("");
}

void	init(t_getname *g, t_read *r, char *tmp)
{
	(*g).i = -1;
	(*g).p = 0;
	(*r).ptr = opendir(tmp);
	(*g).path2 = ft_path(tmp, &g->p, (*g).path2, &g->stock);
}

void	ft_noperm(char *tmp)
{
	struct stat buf;

	lstat(tmp, &buf);
	if (errno == EACCES)
	{
		ft_putstr("ft_ls: ");
		ft_putstr(tmp);
		ft_putstr(": Permission denied");
	}
}
