/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_opt_re.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 01:06:55 by ymarcill          #+#    #+#             */
/*   Updated: 2018/05/24 23:33:19 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ft_tab_loop(char *stock2, char *path2, int p)
{
	t_getname	g;

	g.path3 = stock2;
	stock2 = ft_strjoinnf(path2, g.path3);
	free(g.path3);
	g.path3 = stock2;
	stock2 = stock2[0] == '.' && (stock2[3] == '/'
	|| stock2[3] == '.') ? ft_strdup(&stock2[2]) : ft_strdup(stock2);
	free(g.path3);
	if (p == 1 && stock2[0] == '/' && stock2[1] == '/')
	{
		g.path3 = stock2;
		stock2 = ft_strdup(&stock2[1]);
		free(g.path3);
	}
	return (stock2);
}

void	ft_rec(char *stock2, char *tmp, t_option opt, int a)
{
	t_read	r;

	lstat(stock2, &r.buf);
	if (S_ISDIR(r.buf.st_mode) && ((readlink(tmp, r.tmp, 255)) == -1 || !opt.l))
	{
		if (stock2[ft_strlen(stock2) - 4] != 'f' || stock2[ft_strlen(stock2) -
			3] != 'd')
		{
			ft_putstr("\n");
			ft_putstr(stock2);
			ft_putstr(":\n");
			ls_re_ac2_bis(stock2, a, opt);
		}
	}
}

char	**ft_check(t_option opt, char **stock2, int a, char *path2)
{
	if (opt.t == 1)
		stock2 = ft_its_t(stock2, a, path2);
	else if ((a == 2 || a == 3) && opt.t == 0)
		ft_rev_params(stock2);
	else if ((a == 0 || a == 1) && opt.t == 0)
		ft_sort_params(stock2);
	return (stock2);
}

void	ls_re_ac2_bis(char *tmp, int a, t_option opt)
{
	t_getname	g;
	t_read		r;

	init(&g, &r, tmp);
	if (!r.ptr && errno == EACCES)
	{
		ft_perm_den(tmp, &g.path2, &g.stock);
		return ;
	}
	g.stock2 = ft_stock_loop(&r.ptr, a, &g.stock);
	g.stock2 = ft_check(opt, g.stock2, a, g.path2);
	if (g.stock2[0])
		opt.l ? ft_its_l(a, tmp, opt.t, r.tmp) : ft_print_dir(g.stock2, opt);
	while (g.stock2[++g.i])
	{
		if (!(ft_strlen(g.stock2[g.i]) == 1 && g.stock2[g.i][0] == '.') &&
				!(ft_strlen(g.stock2[g.i]) == 2 && g.stock2[g.i][0] == '.' &&
					g.stock2[g.i][1] == '.'))
		{
			g.stock2[g.i] = ft_tab_loop(g.stock2[g.i], g.path2, g.p);
			ft_rec(g.stock2[g.i], tmp, opt, a);
		}
	}
	g.path2 ? free(g.path2) : 0;
	ft_freetab(g.stock2);
}

void	ls_opt_re(int ac, char **av, t_option opt)
{
	if (ac == 2 && opt.a == 0 && opt.r == 0 && opt.t == 0)
	{
		opt.l ? ls_opt_l(ac, av) : ls_no_option(ac, av, opt.m, 1);
		ls_re_no_ac(".", opt);
	}
	else
	{
		if (opt.a == 0 && opt.r == 0 && opt.t == 0)
			ls_re_no_opt(av, ac, opt);
		else if (opt.a == 1 && opt.r == 0)
			ls_re_opt_a(ac, av, opt);
		else if (opt.a == 0 && opt.r == 1)
			ls_re_opt_r(ac, av, opt);
		else if (opt.a == 1 && opt.r == 1)
			ls_re_opt_ra(ac, av, opt);
		else if (opt.t == 1)
			ls_re_opt_t(ac, av, opt);
	}
}
