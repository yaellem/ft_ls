/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_rights_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 17:36:39 by ymarcill          #+#    #+#             */
/*   Updated: 2018/05/16 20:27:21 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	**ft_stock(char *av, int r, int a, int t)
{
	char	**stock;
	char	**tmp;

	tmp = NULL;
	stock = ft_tri(av, a);
	if (r || t)
	{
		if (t)
		{
			ft_freetab(stock);
			stock = ft_tri_t(av, a);
		}
		if (r)
		{
			tmp = stock;
			stock = reverse_tab(stock);
			ft_freetab(tmp);
		}
	}
	return (stock);
}

void	ft_print(char *stock, char *av, int a, DIR *ptr)
{
	t_param		p;

	p.l = longuest_slink(av, a);
	p.n = longuest_size(av, a);
	l_type(stock, av);
	l_urights(stock, av);
	l_grights(stock, av);
	l_orights(stock, av);
	ft_putstr("  ");
	nbr_link(stock, p.l, av, a);
	ft_putchar(' ');
	l_name(ptr, stock, av, a);
	l_size2(stock, p.n, av, a);
	l_time(ptr, stock, av);
}

void	ft_lnk(char *av, char *stock)
{
	t_read		re;
	t_getname	get;

	if (stock)
	{
		get.path = ft_strjoinnf(av, "/");
		get.path2 = ft_strjoin(get.path, stock);
	}
	else
	{
		get.path2 = av;
		stock = av;
	}
	if ((re.ret = readlink(get.path2, re.tmp, 255) == -1))
		ft_putstr(stock);
	if ((re.ret = readlink(get.path2, re.tmp, 254)) > 1)
	{
		ft_putstr(stock);
		re.tmp[re.ret] = '\0';
		ft_putstr(" -> ");
		ft_putendl(re.tmp);
	}
	else
		ft_putchar('\n');
	stock ? free(get.path2) : ft_putstr("");
}

void	fdp(char *av, int a, DIR *ptr)
{
	ft_print(NULL, av, a, ptr);
	ft_lnk(av, NULL);
}

void	l_rights(char *av, int r, int a, int t)
{
	t_param		param;
	t_read		re;

	param.i = -1;
	re.ptr = opendir(av);
	if ((re.ret = readlink(av, re.tmp, 255)) != -1 && av[ft_strlen(av)] != '/')
	{
		re.ptr ? closedir(re.ptr) : ft_putstr("");
		re.ptr = NULL;
	}
	if (re.ptr)
	{
		re.stock = ft_stock(av, r, a, t);
		while (re.stock[++param.i])
		{
			ft_print(re.stock[param.i], av, a, re.ptr);
			ft_lnk(av, re.stock[param.i]);
		}
		ft_freetab(re.stock);
	}
	if (!re.ptr)
		fdp(av, a, re.ptr);
	re.ptr ? closedir(re.ptr) : ft_putstr("");
}
