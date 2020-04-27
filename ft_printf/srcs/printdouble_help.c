/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printdouble_help.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaji <mnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 23:25:24 by mnaji             #+#    #+#             */
/*   Updated: 2019/11/11 23:39:27 by mnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	nbrlenull(unsigned long long int n)
{
	int		count;

	count = 0;
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static int	printnbrull_fd(unsigned long long int n, int fd)
{
	int		len;

	len = 1;
	if (n > 9)
		printnbrull_fd(n / 10, fd);
	ft_putchar_fd((char)(n % 10 + 48), fd);
	while ((n = n / 10) != 0)
		len++;
	return (len);
}

static int	printnbrull_d_fd(unsigned long long int n, int fd, char conv)
{
	unsigned long long int	tmp;
	int						len;

	ft_putchar('.');
	len = 1;
	tmp = n / 10;
	tmp = tmp % ft_powerof_10(nbrlenull(n) - 2);
	while (nbrlenull(tmp) < nbrlenull(n) - 2)
	{
		ft_putchar_fd('0', fd);
		n = n / 10;
		len++;
	}
	if (n % 10 >= 5)
		tmp++;
	if (conv == 'g' || conv == 'G')
		while (tmp % 10 == 0 && tmp != 0)
			tmp = tmp / 10;
	if (tmp != 0)
		return (len + printnbrull_fd(tmp, fd));
	return (len);
}

int			printdouble_help2(char conv, t_doublenorme d, t_param *param, \
		int fd)
{
	if (param->accur > 0)
	{
		d.db = (d.db - (double)d.integer + 1) * ft_powerof_10(param->accur + 1);
		stock_integer(d.db, &d.integer);
		if ((conv != 'g' && conv != 'G') || d.integer % \
				ft_powerof_10(param->accur + 1) != 0)
			d.len = d.len + printnbrull_d_fd(d.integer, fd, conv);
	}
	if (conv == 'e' || conv == 'E')
	{
		ft_putchar_fd(conv, fd);
		if (d.e >= 0)
			ft_putchar_fd('+', fd);
		else
		{
			ft_putchar_fd('-', fd);
			d.e = -d.e;
		}
		if (d.e < 9 && d.e > -9)
			ft_putchar_fd('0', fd);
		ft_putchar_fd('0' + d.e, fd);
		d.len = d.len + 4;
	}
	return (d.len);
}

void		printdouble_help1(char *conv, t_doublenorme *d, t_param *param)
{
	if (*conv == 'g' || *conv == 'G')
	{
		stock_integer(d->db, &d->integer);
		if (nbrlenull(d->integer) > param->accur)
		{
			*conv = *conv - 2;
			param->accur--;
		}
	}
	if ((*conv == 'e' || *conv == 'E') && d->db != 0)
	{
		while (d->db > 10 || d->db < -10)
		{
			d->db = d->db / 10;
			d->e++;
		}
		while (d->db < 1 && d->db > -1)
		{
			d->db = d->db * 10;
			d->e--;
		}
	}
}
