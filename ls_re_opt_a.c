/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_re_opt_a.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 01:59:53 by ymarcill          #+#    #+#             */
/*   Updated: 2018/05/21 00:11:32 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_its_dir_re_a(char *str, int x, int ac, t_option opt)
{
	if (ac > 3)
	{
		if (x >= 1)
			ft_putstr("\n\n");
		ft_putstr(str);
		ft_putstr(":\n");
	}
	ls_re_ac2_bis(str, 1, opt);
}

void	ls_re_opt_a_arg(int ac, char **av, t_option opt)
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
				opt.l == 1 ? l_rights(av[r.x], 0, 1, opt.t) :
					ft_its_file(av[r.x], opt.m, r.x, ac);
		}
		if (r.ptr)
		{
			closedir(r.ptr);
			ft_its_dir_re_a(av[r.x], r.x, ac, opt);
		}
	}
}

void	ls_re_opt_a(int ac, char **av, t_option opt)
{
	t_getname	g;

	g.x = 0;
	g.y = 0;
	while (av[g.x])
	{
		if (av[g.x][0] == '-' && av[g.x][1] && av[g.x][1] != '-')
			g.y++;
		g.x++;
	}
	if (ac == 2 || g.y == g.x - 1)
	{
		g.stock2 = opt.t == 1 ? ft_tri_t(".", 1) : ft_tri(".", 1);
		!opt.l & !opt.m ? print_tab_a(g.stock2) : print_tab_ma(g.stock2);
		ft_freetab(g.stock2);
		ls_re_ac2_bis(".", 1, opt);
		return ;
	}
	av = opt.t == 1 ? create_tab(ac, av, opt.l, ft_time_params) : create_tab(ac,
	av, opt.l, ft_sort_params);
	if (ac != 2 && g.y != g.x - 1)
		ls_re_opt_a_arg(ac, av, opt);
}
