/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_re_opt_t.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 21:16:07 by ymarcill          #+#    #+#             */
/*   Updated: 2018/05/21 00:12:34 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_its_dir_re_t(char *str, int x, int ac, t_option opt)
{
	if (ac > 3)
	{
		if (x >= 1)
			ft_putchar('\n');
		ft_putstr(str);
		ft_putstr(":\n");
	}
	ls_re_ac2_bis(str, 0, opt);
}

void	ls_re_opt_t_arg(int ac, char **av, t_option opt)
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
				opt.l ? l_rights(av[r.x], opt.r, opt.a, 1) : ft_its_file(av[r.x]
				, opt.m, r.x, ac);
		}
		if (r.ptr)
		{
			closedir(r.ptr);
			ft_its_dir_re_t(av[r.x], r.x, ac, opt);
		}
	}
}

void	ls_re_opt_t(int ac, char **av, t_option opt)
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
	if (ac == 2 || g.y == (ac - 1))
	{
		ls_re_ac2_bis(".", 0, opt);
		return ;
	}
	av = create_tab(ac, av, opt.l, ft_time_params);
	if (ac != 2 && g.y != g.x - 1)
		ls_re_opt_t_arg(ac, av, opt);
}
