/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_opt_t.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 18:06:04 by ymarcill          #+#    #+#             */
/*   Updated: 2018/05/21 00:09:18 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_choose_opt_t(char *str, t_option opt, int x, int ac)
{
	char	**stock;

	stock = ft_tri_t(str, opt.a);
	if (opt.l)
	{
		l_size(NULL, str, opt.a);
		l_rights(str, 0, opt.a, 1);
	}
	else if (opt.a == 1 && !opt.m)
		print_tab_a(stock);
	else if (opt.a == 1 && opt.m == 1)
		print_tab_ma(stock);
	else if (!opt.a && opt.m == 1)
		print_tab_m(stock);
	else if (!opt.a && !opt.m)
		print_tab(stock);
	if ((x + 3 >= ac && !opt.l))
		ft_putchar('\n');
	ft_freetab(stock);
}

void	ft_its_dir_t(t_option opt, int x, int ac, char *str)
{
	if (x != 0 && !opt.l)
		ft_putstr("\n\n");
	if (x && opt.l)
		ft_putchar('\n');
	if (ac != 3)
	{
		ft_putstr(str);
		ft_putstr(":\n");
	}
	ft_choose_opt_t(str, opt, x, ac);
}

void	ls_opt_t_arg(int ac, char **av, t_option opt)
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
				opt.l == 1 ? l_rights(av[x], 0, opt.a, 1) :
				ft_its_file(av[x], opt.m, x, ac);
		}
		if (read.ptr)
		{
			ft_its_dir_t(opt, x, ac, av[x]);
			closedir(read.ptr);
		}
		x++;
	}
}

void	ls_opt_t(int ac, char **av, t_option opt)
{
	int	x;
	int y;

	x = 0;
	y = 0;
	while (av[x])
	{
		if (av[x][0] == '-' && (av[x][1] && av[x][1] != '-'))
			y++;
		x++;
	}
	if (ac == 2 || y == x - 1)
	{
		ft_choose_opt_t(".", opt, x, ac);
		return ;
	}
	av = create_tab(ac, av, opt.l, ft_time_params);
	if (ac != 2 && y != x - 1)
		ls_opt_t_arg(ac, av, opt);
}
