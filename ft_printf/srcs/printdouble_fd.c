/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printdouble_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaji <mnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 22:22:14 by mnaji             #+#    #+#             */
/*   Updated: 2019/11/11 23:48:46 by mnaji            ###   ########.fr       */
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

static int	printdouble_special(char conv, double db, int fd)
{
	if (db == 3 / 0.0)
	{
		if (conv == 'E' || conv == 'G')
			ft_putstr_fd("INF", fd);
		else
			ft_putstr_fd("inf", fd);
		return (3);
	}
	else if (db == -0.0 / 0.0)
	{
		if (conv == 'E' || conv == 'G')
			ft_putstr_fd("-NAN", fd);
		else
			ft_putstr_fd("-nan", fd);
		return (4);
	}
	return (0);
}

int			printdouble_fd(va_list args, int fd, t_param *param, char conv)
{
	t_doublenorme	d;

	ft_bzero(&d, sizeof(t_doublenorme));
	d.db = va_arg(args, double);
	if ((d.len = printdouble_special(conv, d.db, fd)) != 0)
		return (d.len);
	if (param->accur == -1)
		param->accur = 6;
	printdouble_help1(&conv, &d, param);
	if (d.db < 0)
	{
		ft_putchar_fd('-', fd);
		d.db = -d.db;
		d.len++;
	}
	stock_integer(d.db, &d.integer);
	d.len = d.len + printnbrull_fd(d.integer, fd);
	if (conv == 'g' || conv == 'G')
		param->accur = param->accur - nbrlenull(d.integer);
	return (printdouble_help2(conv, d, param, fd));
}
