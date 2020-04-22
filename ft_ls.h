/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 22:31:23 by ymarcill          #+#    #+#             */
/*   Updated: 2018/05/26 16:48:21 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "./libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <grp.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <pwd.h>
# include <time.h>
# include <sys/types.h>
# include <uuid/uuid.h>
# include <errno.h>
# include <stdio.h>

typedef	struct		s_param
{
	int				n;
	int				i;
	int				l;
	char			*x;
}					t_param;

typedef	struct		s_tab
{
	char			**a1;
	char			**a2;
}					t_tab;

typedef	struct		s_option
{
	int				o;
	int				u;
	int				x;
	int				a;
	int				r;
	int				re;
	int				l;
	int				t;
	int				i;
	int				m;
	int				p;
	int				checkl;
	int				checkm;
}					t_option;

typedef	struct		s_read
{
	int				i;
	int				x;
	DIR				*ptr;
	DIR				*ptr2;
	ssize_t			ret;
	struct stat		buf;
	struct stat		buf2;
	struct dirent	*file;
	char			tmp[255];
	char			**stock;
	char			**stock2;
	char			*test;
}					t_read;

typedef	struct		s_getname
{
	DIR				*ptr;
	DIR				*ptr2;
	ssize_t			ret;
	struct stat		buf;
	struct stat		buf2;
	struct dirent	*file;
	char			tmp[255];
	int				i;
	int				y;
	int				p;
	int				x;
	struct passwd	*pws;
	struct group	*grname;
	char			*path;
	char			*path2;
	char			*path3;
	char			**path4;
	char			*path5;
	char			*stock;
	char			**stock2;
	char			**tmp2;
}					t_getname;

void				ft_freetab(char **s1);
char				**ft_tri(char *tmp, int a);
char				**test(char *tmp, DIR *st, int i);
char				**ft_tri_t(char *tmp, int a);
void				print_tab(char **str);
void				print_tab_m(char **str);
void				print_tab_ma(char **str);
void				print_tab_a(char **str);
void				ft_ls_r_stock(char *ptr, t_option opt);
void				ft_sort_params(char **av);
void				ft_time_params(char **av);
void				ft_rev_params(char **av);
void				ft_rev_params2(char **av);
void				nbr_link(char *av, int slink, char *ptr, int a);
int					nbr_size(int a);
int					longuest_slink(char *av, int a);
int					longuest_size(char *av, int a);
char				**create_tab(int ac, char **av, int testl,
		void	ft_sort(char **str));
char				**reverse_tab(char **av);
void				ls_no_option(int ac, char **av, int m, int r);
void				ls_opt_a(int ac, char **av, t_option opt);
void				ls_opt_t(int ac, char **av, t_option opt);
void				ls_opt_l(int ac, char **av);
void				ls_opt_re(int ac, char **av, t_option opt);
void				ls_opt_r(int ac, char **av, t_option opt);
void				l_rights(char *av, int r, int a, int t);
void				l_type(char *stock, char *av);
void				l_urights(char *av, char *pat);
void				l_grights(char *av, char *pat);
void				l_orights(char *av, char *pat);
void				l_size(DIR *str, char *av, int a);
void				l_size2(char *av, int lgsts, char *pat, int a);
void				l_name(DIR *str, char *av, char *pat, int a);
void				l_time(DIR *str, char *av, char *pat);
void				ft_no_access(char *str, int x);
char				**rev_tab(char **av);
void				ft_its_file(char *str, int m, int x, int ac);
void				ft_its_dir_r(t_option opt, int x, int ac, char *str);
void				ft_its_dir_a(char *str, t_option opt, int x, int ac);
void				ft_choose_opt(t_option opt);
void				*ft_link(char *av, DIR *ptr, int l);
void				ls_re_ac2_bis(char *tmp, int a, t_option opt);
void				ls_re_opt_a(int ac, char **av, t_option opt);
void				ls_re_opt_r(int ac, char **av, t_option opt);
void				ls_re_opt_ra(int ac, char **av, t_option opt);
void				ls_re_opt_t(int ac, char **av, t_option opt);
void				ft_print_dir(char **stock2, t_option opt);
void				*ft_path(char *tmp, int *p, char *path2, char **stock);
void				ft_its_l(int a, char *tmp, int t, char *tmp2);
int					ft_perm_den(char *tmp, char **path, char **stock);
char				**ft_stock_loop(DIR **ptr, int a, char **stock);
char				**ft_its_t(char **stock2, int a, char *path2);
void				ls_re_no_opt(char **av, int ac, t_option opt);
void				ls_re_no_ac(char *tmp, t_option opt);
void				init(t_getname *g, t_read *r, char *tmp);
void				ft_noperm(char *tmp);

#endif
