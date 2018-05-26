/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_re_opt_ra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 21:14:45 by ymarcill          #+#    #+#             */
/*   Updated: 2018/05/21 00:12:10 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_its_dir_re_ra(char *str, int x, int ac, t_option opt)
{
	t_read	r;

	if (x == 2)
	{
		r.stock = opt.t ? ft_tri_t(str, 1) : ft_tri(str, 1);
		print_tab_a(r.stock);
	}
	if (ac > 3)
	{
		if (x >= 1 && !opt.l)
			ft_putstr("\n\n");
		if (x >= 1 && opt.l)
			ft_putchar('\n');
		ft_putstr(str);
		ft_putstr(":\n");
	}
	ls_re_ac2_bis(str, 3, opt);
}

void	ls_re_opt_ra_arg(int ac, char **av, t_option opt)
{
	t_read	r;

	r.x = -1;
	while (av[++r.x])
	{
		r.ptr = opendir(av[r.x]);
		r.ptr = ft_link(av[r.x], r.ptr, opt.l);
		if (r.ptr == NULL && lstat(av[r.x], &r.buf) == 0)
		{
			if (errno == EACCES)
				ft_no_access(av[r.x], r.x);
			else
				opt.l ? l_rights(av[r.x], 1, 1, opt.t) : ft_its_file(av[r.x],
				opt.m, r.x, ac);
		}
		if (r.ptr)
		{
			closedir(r.ptr);
			ft_its_dir_re_ra(av[r.x], r.x, ac, opt);
		}
	}
}

void	ls_re_opt_ra(int ac, char **av, t_option opt)
{
	t_getname	g;

	g.x = -1;
	g.y = 0;
	while (av[++g.x])
	{
		if (av[g.x][0] == '-' && av[g.x][1] && av[g.x][1] != '-')
			g.y++;
	}
	if (ac == 2 || g.y == g.x - 1)
	{
		ls_re_ac2_bis(".", 3, opt);
		return ;
	}
	if (opt.t == 1)
	{
		av = create_tab(ac, av, opt.l, ft_time_params);
		av = rev_tab(av);
	}
	else
		av = create_tab(ac, av, opt.l, ft_rev_params);
	if (ac != 2 && g.y != g.x - 1)
		ls_re_opt_ra_arg(ac, av, opt);
	ft_freetab(av);
}
