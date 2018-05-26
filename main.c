/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 02:50:04 by ymarcill          #+#    #+#             */
/*   Updated: 2018/05/22 03:37:06 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_option	ft_find_opt_bis(t_option opt, char **av)
{
	if (av[opt.x][opt.i] == 'm')
	{
		opt.checkm = opt.i;
		opt.m = 1;
	}
	if (av[opt.x][opt.i] == 'r')
		opt.r = 1;
	if (av[opt.x][opt.i] == 'a')
		opt.a = 1;
	if (av[opt.x][opt.i] == 'R')
		opt.re = 1;
	if (av[opt.x][opt.i] == 't')
		opt.t = 1;
	if (av[opt.x][opt.i] == 'l')
	{
		opt.checkl = opt.i;
		opt.l = 1;
	}
	if (av[opt.x][opt.i] == 'p')
		opt.p = 1;
	if (av[opt.x][opt.i] == '/')
		opt.o = 2;
	return (opt);
}

t_option	ft_find_opt(t_option opt, char **av)
{
	while (av[opt.x])
	{
		if (av[opt.x][0] == '-' && av[opt.x][1])
		{
			while (av[opt.x][opt.i++])
				opt = ft_find_opt_bis(opt, av);
		}
		if (av[opt.x] && av[opt.x][0] != '-' && opt.i > 0)
		{
			opt.u = opt.x;
			while (av[opt.u])
			{
				if (av[opt.u][0] == '-')
					break ;
				opt.u++;
			}
			break ;
		}
		opt.i = 0;
		opt.x++;
	}
	return (opt);
}

char		ft_checky(char **av, int ac)
{
	int i;
	int y;

	i = 1;
	y = 0;
	while (y < ac)
	{
		while (av[y][i])
		{
			if (av[y][0] == '-' && av[y][i] != 'R' && av[y][i] != 'r' &&
				av[y][i] != 't' && av[y][i] != 'a' && av[y][i] != 'l' &&
				av[y][i] != 'm')
				return (av[y][i]);
			i++;
		}
		i = 1;
		y++;
	}
	return (0);
}

void		ft_which_opt(int ac, char **av, t_option opt)
{
	if ((ac != 1 && av[1][0] == '-' && av[1][1] && ft_checky(av, ac)) ||
		opt.o == 2)
	{
		if (opt.o == 2)
			av[1][1] = '/';
		ft_putstr("ft_ls: illegal option -- ");
		ft_putchar(ft_checky(av, ac));
		ft_putchar('\n');
		ft_putendl("usage: ft_ls [-lRartm] [file ...]");
	}
	else if (opt.m == 1 && !opt.a && !opt.r && !opt.re && !opt.t && !opt.l)
		ls_no_option(ac, av, opt.m, 0);
	else if (opt.r == 1 && opt.re == 0)
		ls_opt_r(ac, av, opt);
	else if (opt.t == 1 && opt.re == 0 && opt.r == 0)
		ls_opt_t(ac, av, opt);
	else if (opt.r == 0 && opt.re == 0 && opt.a == 1 && opt.t == 0)
		ls_opt_a(ac, av, opt);
	else if (opt.re == 1)
		ls_opt_re(ac, av, opt);
	else if (opt.l == 1 && opt.r == 0 && opt.re == 0 && opt.a == 0 && opt.t ==
			0)
		ls_opt_l(ac, av);
}

int			main(int ac, char **av)
{
	t_option	opt;

	opt.x = 0;
	opt.a = 0;
	opt.r = 0;
	opt.re = 0;
	opt.l = 0;
	opt.t = 0;
	opt.i = 0;
	opt.m = 0;
	opt.p = 0;
	opt.o = 0;
	opt.u = 0;
	opt.checkl = 0;
	opt.checkm = 0;
	if (ac == 1 || av[1][0] != '-' || (av[1][0] == '-' && !av[1][1]))
	{
		ls_no_option(ac, av, opt.m, 0);
		return (0);
	}
	opt = ft_find_opt(opt, av);
	if (opt.l == 1 && opt.m == 1 && opt.checkm > opt.checkl)
		opt.l = 0;
	ft_which_opt(ac, av, opt);
	return (0);
}
