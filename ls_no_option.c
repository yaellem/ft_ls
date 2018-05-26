/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_no_option.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 02:52:49 by ymarcill          #+#    #+#             */
/*   Updated: 2018/05/24 23:20:03 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_is_dir(char *str, int m, int x, int ac)
{
	char	**stock;

	if (x != 0)
		ft_putstr("\n\n");
	if (ac >= 3)
	{
		ft_putstr(str);
		ft_putstr(":\n");
	}
	stock = ft_tri(str, 0);
	if (m)
		print_tab_m(stock);
	else
		print_tab(stock);
	if (x + 3 >= ac)
		ft_putchar('\n');
	ft_freetab(stock);
}

void	ls_no_option(int ac, char **av, int m, int r)
{
	t_read			read;
	char			**stock;

	read.x = -1;
	if (ac == 1 || (ac == 2 && (m == 1 || r == 1)))
	{
		stock = ft_tri(".", 0);
		m == 1 ? print_tab_m(stock) : print_tab(stock);
		ft_putchar('\n');
		ft_freetab(stock);
		return ;
	}
	av = create_tab(ac, av, 0, ft_sort_params);
	while (av[++read.x])
	{
		read.ptr = opendir(av[read.x]);
		if (read.ptr == NULL && lstat(av[read.x], &read.buf) == 0)
			errno == EACCES ? ft_no_access(av[read.x], read.x) :
			ft_its_file(av[read.x], m, read.x, ac);
		if (read.ptr)
		{
			ft_is_dir(av[read.x], m, read.x, ac);
			closedir(read.ptr);
		}
	}
}
