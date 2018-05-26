/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 06:52:37 by ymarcill          #+#    #+#             */
/*   Updated: 2018/05/22 03:28:10 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_sort_params(char **av)
{
	t_param	param;

	param.i = 0;
	param.n = 0;
	while (av[param.n])
	{
		param.i = param.n + 1;
		while (av[param.i])
		{
			if ((ft_strcmp(av[param.n], av[param.i])) > 0 &&
				av[param.n][0] != '-')
			{
				param.x = av[param.n];
				av[param.n] = av[param.i];
				av[param.i] = param.x;
				param.i--;
			}
			param.i++;
		}
		param.n++;
	}
}

void	ft_time_params(char **av)
{
	t_param		param;
	t_read		read;

	param.i = 0;
	param.n = 0;
	while (av[param.n])
	{
		param.i = param.n + 1;
		while (av[param.i])
		{
			lstat(av[param.n], &read.buf);
			lstat(av[param.i], &read.buf2);
			if ((read.buf.st_mtime == read.buf2.st_mtime && ft_strcmp(av[param.
				n], av[param.i]) > 0) || read.buf.st_mtime < read.buf2.st_mtime)
			{
				param.x = av[param.n];
				av[param.n] = av[param.i];
				av[param.i] = param.x;
			}
			param.i++;
		}
		param.n++;
	}
}
