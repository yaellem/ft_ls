/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_re_opt_r.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 21:12:26 by ymarcill          #+#    #+#             */
/*   Updated: 2018/05/18 21:21:12 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_its_dir_re_r(char *str, int x, int ac, t_option opt)
{
	if (ac > 3)
	{
		if (x >= 1)
			ft_putstr("\n\n");
		ft_putstr(str);
		ft_putstr(":\n");
	}
	ls_re_ac2_bis(str, 2, opt);
}

void	ls_re_opt_r_arg(int ac, char **av, t_option opt)
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
				opt.l == 1 ? l_rights(av[r.x], 1, 0, opt.t) :
					ft_its_file(av[r.x], opt.m, r.x, ac);
		}
		if (r.ptr)
		{
			closedir(r.ptr);
			ft_its_dir_re_r(av[r.x], r.x, ac, opt);
		}
	}
}

void	ls_re_opt_r(int ac, char **av, t_option opt)
{
	t_getname	g;

	g.x = 0;
	g.y = 0;
	while (av[g.x])
	{
		if (av[g.x][0] == '-')
			g.y++;
		g.x++;
	}
	if (ac == 2 || g.y == g.x - 1)
	{
		ls_re_ac2_bis(".", 2, opt);
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
		ls_re_opt_r_arg(ac, av, opt);
}
