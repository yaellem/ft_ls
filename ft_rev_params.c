/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 05:08:51 by ymarcill          #+#    #+#             */
/*   Updated: 2018/05/22 00:48:23 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_rev_params(char **av)
{
	t_param	param;

	param.i = 0;
	param.n = 0;
	while (av[param.i])
		param.i++;
	if (param.i == 1 || param.i == 0)
		return ;
	param.i = 1;
	while (av[param.n])
	{
		param.i = param.n + 1;
		while (av[param.i])
		{
			if ((ft_strcmp(av[param.n], av[param.i])) < 0)
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

int		ft_si(char **av)
{
	int i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}

char	**rev_tab(char **av)
{
	t_param		param;
	t_read		read;

	param.n = ft_si(av);
	param.l = param.n;
	if (!(read.stock = malloc(sizeof(char*) * (param.n + 1))))
		return (NULL);
	while (--param.n >= 0)
	{
		lstat(av[param.n], &read.buf);
		if (S_ISDIR(read.buf.st_mode) == 0)
			read.stock[param.i++] = ft_strdup(av[param.n]);
	}
	param.n = param.l;
	while (--param.n >= 0)
	{
		if (av[param.n][0] == '-')
			break ;
		lstat(av[param.n], &read.buf);
		if (S_ISDIR(read.buf.st_mode))
			read.stock[param.i++] = ft_strdup(av[param.n]);
	}
	read.stock[param.i] = NULL;
	return (read.stock);
}

void	ft_no_access(char *str, int x)
{
	if (x != 0)
		ft_putstr("\n\n");
	ft_putstr(str);
	ft_putendl(":");
	ft_putstr("ft_ls: ");
	ft_putstr(str);
	ft_putendl(": Permission denied");
}
