/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_opt_a.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 07:01:27 by ymarcill          #+#    #+#             */
/*   Updated: 2018/05/21 00:10:35 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_choose_opt(t_option opt)
{
	char	**stock;

	stock = ft_tri(".", 1);
	if (opt.l)
	{
		l_size(NULL, ".", 1);
		l_rights(".", 0, 1, 0);
	}
	else if (opt.m)
		print_tab_ma(stock);
	else if (!opt.m && !opt.l)
		print_tab_a(stock);
	if (!opt.l)
		ft_putchar('\n');
	ft_freetab(stock);
}

void		ft_its_dir_a(char *str, t_option opt, int x, int ac)
{
	char	**stock;
	char	tmp[255];

	x != 0 && !opt.l ? ft_putstr("\n\n") : ft_putstr("");
	x != 0 && opt.l == 1 ? ft_putchar('\n') : ft_putstr("");
	if (ac > 3)
	{
		ft_putstr(str);
		ft_putstr(":\n");
	}
	stock = ft_tri(str, 1);
	if (opt.l)
	{
		if ((readlink(str, tmp, 255)) == -1)
			l_size(NULL, str, 1);
		l_rights(str, 0, 1, 0);
	}
	else if (opt.m)
		print_tab_ma(stock);
	else if (!opt.m && !opt.l)
		print_tab_a(stock);
	if (!opt.l && x + 3 > ac)
		ft_putchar('\n');
	ft_freetab(stock);
}

void		ls_opt_a_arg(int ac, char **av, t_option opt)
{
	t_read	read;

	read.x = -1;
	while (av[++read.x])
	{
		read.ptr = opendir(av[read.x]);
		read.ptr = ft_link(av[read.x], read.ptr, opt.l);
		if (read.ptr == NULL && lstat(av[read.x], &read.buf) == 0)
		{
			if (errno == EACCES)
				ft_no_access(av[read.x], read.x);
			else
				opt.l == 1 ? l_rights(av[read.x], 0, 1, 0) :
				ft_its_file(av[read.x], opt.m, read.x, ac);
		}
		if (read.ptr)
		{
			ft_its_dir_a(av[read.x], opt, read.x, ac);
			closedir(read.ptr);
		}
	}
}

void		ls_opt_a(int ac, char **av, t_option opt)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (av[x])
	{
		if (av[x][0] == '-' && av[x][1] && av[x][1] != '-')
			y++;
		x++;
	}
	if (ac == 2 || y == x - 1)
	{
		ft_choose_opt(opt);
		return ;
	}
	av = create_tab(ac, av, opt.l, ft_sort_params);
	if (ac != 2 && y != x - 1)
		ls_opt_a_arg(ac, av, opt);
}
