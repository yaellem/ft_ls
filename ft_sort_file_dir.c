/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_file_dir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 07:28:25 by ymarcill          #+#    #+#             */
/*   Updated: 2018/05/24 23:15:48 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_is_file(char *av, int testl, int y)
{
	t_read	r;

	r.ptr = opendir(av);
	if ((readlink(av, r.tmp, 255)) != -1 && testl == 1)
	{
		r.ptr ? closedir(r.ptr) : 0;
		r.ptr = NULL;
	}
	if (av[0] == '-' && av[1] && y)
	{
		r.ptr ? closedir(r.ptr) : 0;
		return (3);
	}
	else if (r.ptr == NULL && lstat(av, &r.buf) != 0 && errno != EACCES)
		return (2);
	else if (r.ptr == NULL && ((lstat(av, &r.buf) == 0) && errno != EACCES))
		return (1);
	else if (r.ptr == NULL && lstat(av, &r.buf) == -1 && errno == EACCES)
	{
		ft_noperm(av);
		ft_putchar('\n');
		return (5);
	}
	r.ptr ? closedir(r.ptr) : 0;
	return (0);
}

void	ft_tab_in_loop(char **a1, char **a2, char **av, int testl)
{
	t_param	param;

	param.i = 0;
	param.n = 0;
	param.l = 0;
	while (av[++param.i])
	{
		if (av[param.i] && ft_is_file(av[param.i], testl, param.i) == 3)
			param.i++;
		if (av[param.i] && ft_is_file(av[param.i], testl, param.i) == 5)
			break ;
		if (av[param.i] && ft_is_file(av[param.i], testl, param.i) == 1)
			a1[param.n++] = ft_strdup(av[param.i]);
		else if (av[param.i] && ft_is_file(av[param.i], testl, param.i) == 0)
			a2[param.l++] = ft_strdup(av[param.i]);
		else if (av[param.i] && ft_is_file(av[param.i], testl, param.i) == 2)
		{
			ft_putstr("ft_ls: ");
			ft_putstr(av[param.i]);
			ft_putendl(": No such file or directory");
		}
	}
	a1[param.n] = NULL;
	a2[param.l] = NULL;
}

char	**create_tab(int ac, char **av, int testl, void ft_sort(char **str))
{
	t_tab	tab;
	t_param	param;

	param.l = 0;
	param.i = 0;
	param.n = 0;
	if (!(tab.a1 = malloc(sizeof(char*) * ac)) ||
		!(tab.a2 = malloc(sizeof(char*) * ac)))
		return (NULL);
	if (ac > 2)
		ft_sort_params(av + 1);
	ft_tab_in_loop(tab.a1, tab.a2, av, testl);
	if (tab.a1)
		ft_sort(tab.a1);
	if (tab.a2)
		ft_sort(tab.a2);
	while (tab.a1[param.n])
		av[param.i++] = tab.a1[param.n++];
	while (tab.a2[param.l])
		av[param.i++] = tab.a2[param.l++];
	av[param.i] = NULL;
	free(tab.a2);
	free(tab.a1);
	return (av);
}
