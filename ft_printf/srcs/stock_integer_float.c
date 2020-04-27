/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_integer_float.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaji <mnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 22:29:38 by mnaji             #+#    #+#             */
/*   Updated: 2019/11/11 22:37:09 by mnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	init_si(t_varfloat *varf, double db)
{
	varf->c = (unsigned char*)(&db);
	varf->exp = ((varf->c[7] % 128) * 16) + (varf->c[6] / 16) - 1023;
	varf->i = 6;
	varf->mod = 16;
	varf->di = 8;
}

void		stock_integer(double db, unsigned long long int *stock)
{
	t_varfloat	varf;

	ft_bzero(&varf, sizeof(t_varfloat));
	init_si(&varf, db);
	if (varf.exp >= 0)
	{
		*stock = 1;
		while (varf.exp-- > 0)
		{
			*stock = *stock * 2 + varf.c[varf.i] % varf.mod / varf.di;
			if (varf.di == 1)
			{
				varf.mod = 256;
				varf.di = 128;
				varf.i--;
			}
			else
			{
				varf.mod = varf.mod / 2;
				varf.di = varf.di / 2;
			}
		}
	}
	else
		*stock = 0;
}
