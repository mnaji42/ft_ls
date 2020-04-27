/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printnbr_help.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaji <mnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 23:44:49 by mnaji             #+#    #+#             */
/*   Updated: 2019/11/11 23:46:31 by mnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_nbrlen(int n, t_param *param)
{
	int		count;

	count = 0;
	if (n == 0)
		count++;
	if (n < 0)
		count++;
	else if (param->flags.fplus == 1 || param->flags.fspace == 1)
		count++;
	while (n != 0)
	{
		n = (n / 10);
		count++;
	}
	return (count);
}

int		accur_nbr(int n, t_param *param)
{
	int		count;

	count = param->accur;
	if (n < 0)
		count++;
	else if (param->flags.fplus == 1 || param->flags.fspace == 1)
		count++;
	if (count > ft_nbrlen(n, param))
		return (count);
	return (ft_nbrlen(n, param));
}

int		u_nbrlen(int n)
{
	int		count;

	count = 0;
	if (n == 0)
		count++;
	while (n != 0)
	{
		n = (n / 10);
		count++;
	}
	return (count);
}

int		printnbr2_fd(int n, int fd)
{
	int		len;

	len = 1;
	if (n == -2147483648)
	{
		ft_putstr_fd("2147483648", fd);
		return (10);
	}
	if (n < 0)
		n = -n;
	if (n > 9)
		printnbr2_fd(n / 10, fd);
	ft_putchar_fd((char)(n % 10 + 48), fd);
	while ((n = n / 10) != 0)
		len++;
	return (len);
}
