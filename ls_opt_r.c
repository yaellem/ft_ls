/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_opt_r.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 05:06:05 by ymarcill          #+#    #+#             */
/*   Updated: 2018/05/22 00:58:49 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_its_file(char *str, int m, int x, int ac)
{
	ft_putstr(str);
	if (m)
		ft_putstr(", ");
	if (x + 3 < ac)
		ft_putchar('\t');
	if (x + 2 >= ac - 2)
		ft_putchar('\n');
}

void	ft_its_dir_r(t_option opt, int x, int ac, char *str)
{
	if (x != 0 && !opt.l)
		ft_putstr("\n\n");
	else if (x != 0 && opt.l)
		ft_putchar('\n');
	if (ac != 3)
	{
		ft_putstr(str);
		ft_putstr(":\n");
	}
	ft_ls_r_stock(str, opt);
	if (!opt.l && x + 1 > ac)
		ft_putchar('\n');
}

void	ls_opt_r_arg(int ac, char **av, t_option opt)
{
	int		x;
	t_read	read;

	x = 0;
	while (av[x])
	{
		read.ptr = opendir(av[x]);
		read.ptr = ft_link(av[x], read.ptr, opt.l);
		if (read.ptr == NULL && lstat(av[x], &read.buf) == 0)
		{
			if (errno == EACCES)
				ft_no_access(av[x], x);
			else
				opt.l == 1 ? l_rights(av[x], 1, opt.a, opt.t) :
				ft_its_file(av[x], opt.m, x, ac);
		}
		if (read.ptr)
		{
			ft_its_dir_r(opt, x, ac, av[x]);
			closedir(read.ptr);
		}
		x++;
	}
}

void	ls_opt_r(int ac, char **av, t_option opt)
{
	int		x;
	int		y;

	x = -1;
	y = 0;
	while (av[++x])
	{
		if (av[x][0] == '-' && av[x][1] && av[x][1] != '-')
			y++;
	}
	if (ac == 2 || y == x - 1)
	{
		ft_ls_r_stock(".", opt);
		return ;
	}
	if (opt.t == 1)
	{
		av = create_tab(ac, av, opt.l, ft_time_params);
		av = rev_tab(av);
	}
	else
		av = create_tab(ac, av, opt.l, ft_rev_params);
	if (ac != 2 && y != x - 1)
		ls_opt_r_arg(ac, av, opt);
}
