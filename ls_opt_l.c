/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_opt_l.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 18:08:30 by ymarcill          #+#    #+#             */
/*   Updated: 2018/05/21 00:10:18 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_its_dir_l(char *str, int x, int ac)
{
	char **stock;

	if (x != 0)
		ft_putstr("\n");
	if (ac > 3)
	{
		ft_putstr(str);
		ft_putstr(":\n");
	}
	stock = ft_tri(str, 0);
	l_size(NULL, str, 0);
	l_rights(str, 0, 0, 0);
	ft_freetab(stock);
}

void		ls_opt_l_arg(int ac, char **av)
{
	int		x;
	t_read	read;

	x = -1;
	while (av[++x])
	{
		read.ptr = opendir(av[x]);
		if ((readlink(av[x], read.tmp, 255)) != -1)
		{
			read.ptr ? closedir(read.ptr) : ft_putstr("");
			read.ptr = NULL;
		}
		if (read.ptr == NULL && lstat(av[x], &read.buf) == 0)
		{
			if (errno == EACCES)
				ft_no_access(av[x], x);
			else
				l_rights(av[x], 0, 0, 0);
		}
		if (read.ptr)
		{
			ft_its_dir_l(av[x], x, ac);
			closedir(read.ptr);
		}
	}
}

void		ls_opt_l(int ac, char **av)
{
	int				x;
	int				i;
	char			**stock;

	x = 0;
	i = 0;
	while (av[x])
	{
		if (av[x][0] == '-' && av[x][1] && av[x][1] != '-')
			i++;
		x++;
	}
	if (ac == 2 || (i == x - 1))
	{
		stock = ft_tri(".", 0);
		l_size(NULL, ".", 0);
		l_rights(".", 0, 0, 0);
		ft_freetab(stock);
		return ;
	}
	av = create_tab(ac, av, 1, ft_sort_params);
	if (ac != 2 && i != x - 1)
		ls_opt_l_arg(ac, av);
}
