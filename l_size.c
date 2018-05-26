/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_size.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 21:43:11 by ymarcill          #+#    #+#             */
/*   Updated: 2018/05/16 19:39:08 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	l_size(DIR *str, char *av, int a)
{
	struct dirent	*file;
	struct stat		buf;
	int				b;
	char			*path;
	char			*path2;

	if (!str)
		str = opendir(av);
	b = 0;
	path = ft_strjoinnf(av, "/");
	while (str && (file = readdir(str)))
	{
		if (a == 0 && file->d_name[0] == '.')
			continue ;
		path2 = ft_strjoinnf(path, file->d_name);
		lstat(path2, &buf);
		b += buf.st_blocks;
		free(path2);
	}
	ft_putstr("total ");
	ft_putnbr(b);
	ft_putchar('\n');
	free(path);
	if (str)
		closedir(str);
}

int		nbr_size(int a)
{
	char	*str;
	int		ret;

	str = ft_itoa(a);
	ret = ft_strlen(str);
	free(str);
	return (ret);
}

int		longuest_slink(char *av, int a)
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
		c = nbr_size(read.buf.st_nlink);
		if (c >= b)
			b = c;
	}
	free(get.path2);
	read.ptr ? closedir(read.ptr) : ft_putstr("");
	return (b);
}

void	print_nbr_link(int i, int slink, struct stat buf, char *path2)
{
	i = nbr_size(buf.st_nlink);
	if (i < slink)
	{
		while (i++ < slink)
			ft_putchar(' ');
	}
	ft_putnbr(buf.st_nlink);
	free(path2);
}

void	nbr_link(char *av, int slink, char *pat, int a)
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
	read.ptr2 = opendir(get.path2);
	if (a == 0 && av[0] == '.')
	{
		read.ptr2 ? closedir(read.ptr2) : ft_putstr("");
		return ;
	}
	read.ptr ? lstat(get.path2, &read.buf) : lstat(get.path, &read.buf);
	print_nbr_link(get.i, slink, read.buf, get.path2);
	read.ptr2 ? closedir(read.ptr2) : ft_putstr("");
	read.ptr ? closedir(read.ptr) : ft_putstr("");
}
