/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_for_rec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 22:29:29 by ymarcill          #+#    #+#             */
/*   Updated: 2018/05/22 01:03:37 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	*ft_path(char *tmp, int *p, char *path2, char **stock)
{
	char	*path5;
	char	*path;

	path = tmp[0] == '.' && tmp[1] == '/' ? ft_strdup(&tmp[2]) : ft_strdup(tmp);
	if (tmp[0] == '~' || tmp[0] == '/' || tmp[0] == '$')
	{
		*p = 1;
		path5 = ft_strdup("/");
	}
	else
		path5 = ft_strdup("./");
	*stock = ft_strdup("/");
	path2 = ft_strjoin(path5, path);
	free(path);
	path2 = ft_strjoin(path2, *stock);
	return (path2);
}

void	ft_its_l(int a, char *tmp, int t, char *tmp2)
{
	if (a == 0)
	{
		if ((readlink(tmp, tmp2, 255)) == -1)
			l_size(NULL, tmp, 0);
		l_rights(tmp, 0, 0, t);
	}
	if (a == 1)
	{
		if ((readlink(tmp, tmp2, 255)) == -1)
			l_size(NULL, tmp, 1);
		l_rights(tmp, 0, 1, t);
	}
	else if (a == 2)
	{
		if ((readlink(tmp, tmp2, 255)) == -1)
			l_size(NULL, tmp, 0);
		l_rights(tmp, 1, 0, t);
	}
	else if (a == 3)
	{
		if ((readlink(tmp, tmp2, 255)) == -1)
			l_size(NULL, tmp, 1);
		l_rights(tmp, 1, 1, t);
	}
}

int		ft_perm_den(char *tmp, char **path, char **stock)
{
	ft_putstr("ft_ls: ");
	if (tmp[0] == '.')
		tmp = ft_strrchr(tmp, '/');
	ft_putstr(tmp);
	ft_putstr(": ");
	ft_putendl("Permission denied");
	free(*path);
	free(*stock);
	return (1);
}

char	**ft_stock_loop(DIR **ptr, int a, char **stock)
{
	t_read	r;

	while (*ptr && (r.file = readdir(*ptr)) != NULL)
	{
		if (a == 1 || a == 3)
		{
			*stock = ft_strjoin(*stock, r.file->d_name);
			*stock = ft_strjoin(*stock, "/");
		}
		else if ((!a || a == 2) && r.file->d_name[0] != '.')
		{
			*stock = ft_strjoin(*stock, r.file->d_name);
			*stock = ft_strjoin(*stock, "/");
		}
	}
	*ptr ? closedir(*ptr) : ft_putstr("");
	r.stock2 = ft_strsplit(*stock, '/');
	free(*stock);
	return (r.stock2);
}

char	**ft_its_t(char **stock2, int a, char *path2)
{
	t_getname	g;

	g.i = -1;
	while (stock2[++g.i])
	{
		g.path3 = stock2[g.i];
		stock2[g.i] = ft_strjoinnf(path2, g.path3);
		free(g.path3);
	}
	ft_time_params(stock2);
	if (a == 2 || a == 3)
	{
		g.tmp2 = stock2;
		stock2 = reverse_tab(stock2);
		ft_freetab(g.tmp2);
	}
	g.i = 0;
	while (stock2[g.i])
	{
		g.path3 = stock2[g.i];
		stock2[g.i] = ft_strdup(ft_strrchr(stock2[g.i], '/'));
		free(g.path3);
		g.i++;
	}
	return (stock2);
}
