/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_rights.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 00:45:13 by ymarcill          #+#    #+#             */
/*   Updated: 2018/05/16 20:06:17 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ntm(char *stock, char *path, char *path2)
{
	free(path2);
	!stock ? free(path) : ft_putstr("");
}

void	l_type(char *stock, char *av)
{
	t_read		read;
	t_getname	get;

	read.ptr = opendir(av);
	get.path = ft_strdup(av);
	if (read.ptr && lstat(av, &read.buf) == 0 && !S_ISLNK(read.buf.st_mode))
		get.path = ft_strjoin(get.path, "/");
	get.path2 = stock ? ft_strjoin(get.path, stock) : ft_strdup(get.path);
	!read.ptr ? lstat(get.path, &read.buf) : lstat(get.path2, &read.buf);
	if (S_ISDIR(read.buf.st_mode))
		ft_putchar('d');
	else if (S_ISREG(read.buf.st_mode))
		ft_putchar('-');
	else if (S_ISCHR(read.buf.st_mode))
		ft_putchar('c');
	else if (S_ISBLK(read.buf.st_mode))
		ft_putchar('b');
	else if (S_ISFIFO(read.buf.st_mode))
		ft_putchar('p');
	else if (S_ISLNK(read.buf.st_mode))
		ft_putchar('l');
	else if (S_ISSOCK(read.buf.st_mode))
		ft_putchar('s');
	ntm(stock, get.path, get.path2);
	read.ptr ? closedir(read.ptr) : ft_putstr("");
}

void	l_urights(char *av, char *pat)
{
	t_read		read;
	t_getname	get;

	read.ptr = opendir(pat);
	get.path = ft_strdup(pat);
	if (read.ptr && lstat(pat, &read.buf) == 0 && !S_ISLNK(read.buf.st_mode))
		get.path = ft_strjoin(get.path, "/");
	get.path2 = av ? ft_strjoin(get.path, av) : ft_strdup(get.path);
	!read.ptr ? lstat(get.path, &read.buf) : lstat(get.path2, &read.buf);
	(read.buf.st_mode & S_IRUSR) != 0 ? ft_putchar('r') : ft_putchar('-');
	(read.buf.st_mode & S_IWUSR) != 0 ? ft_putchar('w') : ft_putchar('-');
	if (S_ISUID & read.buf.st_mode)
		(S_IXUSR & read.buf.st_mode) ? ft_putchar('s') : ft_putchar('S');
	else if ((S_IXUSR & read.buf.st_mode))
		ft_putchar('x');
	else if (!(S_IXUSR & read.buf.st_mode))
		ft_putchar('-');
	free(get.path2);
	!av ? free(get.path) : ft_putstr("");
	read.ptr ? closedir(read.ptr) : ft_putstr("");
}

void	l_grights(char *av, char *pat)
{
	t_read		read;
	t_getname	get;

	read.ptr = opendir(pat);
	get.path = ft_strdup(pat);
	if (read.ptr && lstat(pat, &read.buf) == 0 && !S_ISLNK(read.buf.st_mode))
		get.path = ft_strjoin(get.path, "/");
	get.path2 = av ? ft_strjoin(get.path, av) : ft_strdup(get.path);
	!read.ptr ? lstat(get.path, &read.buf) : lstat(get.path2, &read.buf);
	(read.buf.st_mode & S_IRGRP) != 0 ? ft_putchar('r') : ft_putchar('-');
	(read.buf.st_mode & S_IWGRP) != 0 ? ft_putchar('w') : ft_putchar('-');
	if ((S_ISGID & read.buf.st_mode))
		(S_IXGRP & read.buf.st_mode) ? ft_putchar('s') : ft_putchar('S');
	else if ((S_IXGRP & read.buf.st_mode))
		ft_putchar('x');
	else if (!(S_IXGRP & read.buf.st_mode))
		ft_putchar('-');
	free(get.path2);
	!av ? free(get.path) : ft_putstr("");
	read.ptr ? closedir(read.ptr) : ft_putstr("");
}

void	l_orights(char *av, char *pat)
{
	t_read		read;
	t_getname	get;

	read.ptr = opendir(pat);
	get.path = ft_strdup(pat);
	if (read.ptr && lstat(pat, &read.buf) == 0 && !S_ISLNK(read.buf.st_mode))
		get.path = ft_strjoin(get.path, "/");
	get.path2 = av ? ft_strjoin(get.path, av) : ft_strdup(get.path);
	!read.ptr ? lstat(get.path, &read.buf) : lstat(get.path2, &read.buf);
	(read.buf.st_mode & S_IROTH) != 0 ? ft_putchar('r') : ft_putchar('-');
	(read.buf.st_mode & S_IWOTH) != 0 ? ft_putchar('w') : ft_putchar('-');
	if ((S_ISVTX & read.buf.st_mode))
		(S_IXOTH & read.buf.st_mode) ? ft_putchar('t') : ft_putchar('T');
	else if ((S_IXOTH & read.buf.st_mode))
		ft_putchar('x');
	else if (!(S_IXOTH & read.buf.st_mode))
		ft_putchar('-');
	free(get.path2);
	!av ? free(get.path) : ft_putstr("");
	read.ptr ? closedir(read.ptr) : ft_putstr("");
}
