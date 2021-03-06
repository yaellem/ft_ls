/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 05:00:50 by ymarcill          #+#    #+#             */
/*   Updated: 2018/05/26 16:35:42 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sort_int(int *tab)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (tab[i])
	{
		j = i + 1;
		while (tab[j])
		{
			if (tab[j] < tab[i])
			{
				ft_swap(&tab[j], &tab[i]);
				j--;
			}
			j++;
		}
		i++;
	}
}
