/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_opt_re_bis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 23:18:00 by ymarcill          #+#    #+#             */
/*   Updated: 2018/05/24 23:28:51 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_its_dir_re_no_ac(int ac, int x, t_option opt, char *str)
{
	t_read	r;

	if (x >= 1 && !opt.l)
		ft_putstr("\n\n");
	else if (x >= 1 && opt.l)
		ft_putchar('\n');
	if (ac > 3 && ((readlink(str, r.tmp, 255)) == -1 || !opt.l))
	{
		ft_putstr(str);
		ft_putstr(":\n");
	}
	ls_re_ac2_bis(str, 0, opt);
}

void	ls_re_no_opt(char **av, int ac, t_option opt)
{
	t_read	r;

	r.x = -1;
	r.i = 0;
	av = create_tab(ac, av, opt.l, ft_sort_params);
	while (av[++r.x])
	{
		r.ptr = opendir(av[r.x]);
		r.ptr = ft_link(av[r.x], r.ptr, opt.l);
		if (r.ptr == NULL && lstat(av[r.x], &r.buf) == 0)
			opt.l == 1 ? l_rights(av[r.x], 0, 0, 0) : ft_its_file(av[r.x],
					opt.m, r.x, ac);
		if (r.ptr)
		{
			closedir(r.ptr);
			ft_its_dir_re_no_ac(ac, r.x, opt, av[r.x]);
		}
	}
}

void	ls_re_no_ac(char *tmp, t_option opt)
{
	t_read	r;

	r.i = 0;
	r.stock = ft_tri(tmp, opt.a);
	while (r.stock[r.i])
	{
		lstat(r.stock[r.i], &r.buf);
		if (S_ISDIR(r.buf.st_mode))
		{
			ft_putchar('\n');
			ft_putstr("./");
			ft_putstr(r.stock[r.i]);
			ft_putendl(":");
			ls_re_ac2_bis(r.stock[r.i], 0, opt);
		}
		r.i++;
	}
	ft_freetab(r.stock);
}
