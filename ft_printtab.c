/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printtab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 15:33:15 by ymarcill          #+#    #+#             */
/*   Updated: 2018/05/21 01:41:32 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_tab(char **str)
{
	int i;
	int x;

	i = 0;
	x = 0;
	while (str[i])
	{
		if (x)
			ft_putstr("\t\t");
		if (str[i][0] != '.')
		{
			x = 1;
			ft_putstr(str[i]);
		}
		i++;
	}
}

void	print_tab_m(char **str)
{
	int i;
	int x;

	i = 0;
	x = 0;
	while (str[i])
	{
		if (x && str[i])
			ft_putstr(", ");
		if (str[i][0] != '.')
		{
			x = 1;
			ft_putstr(str[i]);
		}
		i++;
	}
}

void	print_tab_ma(char **str)
{
	int i;
	int x;

	i = 0;
	x = 0;
	while (str[i])
	{
		if (x && str[i])
			ft_putstr(", ");
		x = 1;
		ft_putstr(str[i]);
		i++;
	}
}

void	print_tab_a(char **str)
{
	int i;
	int x;

	i = 0;
	x = 0;
	while (str[i])
	{
		if (x)
			ft_putchar('\t');
		x = 1;
		ft_putstr(str[i]);
		ft_putchar('\t');
		i++;
	}
}

void	ft_print_dir(char **stock2, t_option opt)
{
	int i;

	i = 0;
	if (!stock2)
		return ;
	while (stock2[i])
	{
		ft_putstr(stock2[i]);
		if (opt.m == 1 && stock2[i + 1])
			ft_putstr(", ");
		else if (!opt.m && !opt.l)
			ft_putstr("\t\t");
		i++;
	}
	ft_putchar('\n');
}
