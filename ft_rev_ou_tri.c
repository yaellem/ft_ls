/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_ou_tri.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 10:40:43 by ymarcill          #+#    #+#             */
/*   Updated: 2018/05/22 03:16:12 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_ls_r_stock(char *ptr, t_option opt)
{
	int		j;
	char	tmp[255];
	char	**rev;

	j = 0;
	rev = opt.t == 1 ? ft_tri_t(ptr, opt.a) : ft_tri(ptr, opt.a);
	while (rev[j])
		j++;
	while (--j >= 0 && !opt.l)
	{
		if (!opt.a && rev[j][0] == '.')
			continue ;
		ft_putstr(rev[j]);
		opt.m == 1 && j != 0 ? ft_putstr(", ") : ft_putchar('\t');
	}
	if (!opt.l)
		ft_putchar('\n');
	if (opt.l)
	{
		if ((readlink(ptr, tmp, 255)) == -1)
			l_size(NULL, ptr, 0);
		l_rights(ptr, 1, opt.a, opt.t);
	}
	ft_freetab(rev);
}

char	**ft_tri(char *tmp, int a)
{
	t_read	read;
	char	**stock;
	int		i;

	i = 0;
	read.ptr = opendir(tmp);
	while (read.ptr && (read.file = readdir(read.ptr)))
		i++;
	if (!(stock = malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i = 0;
	read.ptr ? closedir(read.ptr) : ft_noperm(tmp);
	read.ptr = opendir(tmp);
	while (read.ptr && (read.file = readdir(read.ptr)))
	{
		if (read.file->d_name[0] == '.' && !a)
			continue ;
		stock[i++] = ft_strdup(read.file->d_name);
	}
	stock[i] = NULL;
	ft_sort_params(stock);
	read.ptr ? closedir(read.ptr) : 0;
	return (stock);
}

void	ft_fill_tab(char **stock, DIR *ptr, int a, char *path)
{
	t_read		read;
	t_getname	get;
	int			i;

	i = 0;
	while (ptr && (read.file = readdir(ptr)))
	{
		if (!a && read.file->d_name[0] == '.')
			continue ;
		stock[i] = ft_strdup(read.file->d_name);
		get.path2 = stock[i];
		stock[i] = ft_strjoinnf(path, stock[i]);
		free(get.path2);
		i++;
	}
	stock[i] = NULL;
	ft_time_params(stock);
	i = 0;
	while (stock[i])
	{
		get.path3 = stock[i];
		stock[i] = ft_strdup(ft_strrchr(stock[i], '/'));
		free(get.path3);
		i++;
	}
}

char	**ft_tri_t(char *tmp, int a)
{
	t_read		read;
	t_getname	get;
	int			i;

	i = 0;
	read.ptr = opendir(tmp);
	get.path = ft_strdup(tmp);
	get.path = ft_strjoin(get.path, "/");
	while (read.ptr && (read.file = readdir(read.ptr)))
		i++;
	if (!(read.stock = malloc(sizeof(char*) * (i + 1))))
	{
		read.ptr ? closedir(read.ptr) : 0;
		return (NULL);
	}
	read.ptr ? closedir(read.ptr) : ft_noperm(tmp);
	i = 0;
	read.ptr = opendir(tmp);
	ft_fill_tab(read.stock, read.ptr, a, get.path);
	read.ptr ? closedir(read.ptr) : 0;
	free(get.path);
	return (read.stock);
}

char	**reverse_tab(char **av)
{
	int		i;
	int		y;
	char	**stock;

	i = 0;
	y = 0;
	if (!av)
		return (NULL);
	while (av[i])
		i++;
	if (!(stock = malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i--;
	while (i >= 0)
	{
		if (av[i][0] == '-')
			break ;
		stock[y] = ft_strdup(av[i]);
		y++;
		i--;
	}
	stock[y] = NULL;
	return (stock);
}
