/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printbase.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaji <mnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 21:53:14 by mnaji             #+#    #+#             */
/*   Updated: 2019/11/13 20:24:32 by mnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	nbrlen_base(unsigned int n, int base)
{
	int		count;

	count = 0;
	if (n == 0)
		count++;
	while (n != 0)
	{
		n = (n / base);
		count++;
	}
	return (count);
}

static int	accur_base(unsigned int n, t_param *param)
{
	if (nbrlen_base(n, param->base) < param->accur)
		return (param->accur);
	return (nbrlen_base(n, param->base));
}

int			totallen_base(unsigned int n, t_param *param)
{
	int		count;

	count = 0;
	if (param->flags.fcsharp == 1 && param->base == 8 && n != 0)
	{
		if (param->accur < nbrlen_base(n, param->base) + 1)
			count++;
	}
	else if (param->flags.fcsharp == 1 && param->base != 10 && n != 0)
		count = 2;
	count = count + accur_base(n, param);
	return (count);
}

static int	printbase_help(unsigned int n, int fd, t_param *param, int len)
{
	int		tmp;

	if (param->width > nbrlen_base(n, param->base) && param->flags.fminus == 0)
		while (param->width-- > totallen_base(n, param))
		{
			ft_putchar_fd('0', fd);
			len++;
		}
	tmp = param->accur;
	while (tmp-- > nbrlen_base(n, param->base))
		ft_putchar_fd('0', fd);
	if (!(n == 0 && param->accur == 0 && param->flags.fcsharp == 0) \
			&& param->base != 16)
		len = len + printbase2_fd(n, fd, param);
	else if (!(n == 0 && param->accur == 0) && param->base == 16)
		len = len + printbase2_fd(n, fd, param);
	if (param->width > totallen_base(n, param) && param->flags.fminus == 1)
		while (param->width-- > totallen_base(n, param))
		{
			ft_putchar_fd(' ', fd);
			len++;
		}
	return (len);
}

int			printbase_fd(unsigned int n, int fd, t_param *param)
{
	int		len;

	len = 0;
	if (n == 0 && param->accur == 0)
		param->width++;
	if (param->width > totallen_base(n, param) && param->flags.fminus == 0 \
			&& (param->flags.f0 == 0 || param->accur != -1))
		while (param->width-- > totallen_base(n, param))
		{
			ft_putchar_fd(' ', fd);
			len++;
		}
	if (param->flags.fcsharp == 1 && n != 0)
	{
		if (param->base == 2)
			ft_putstr_fd("0b", fd);
		else if (param->base == 8 && param->accur < \
				nbrlen_base(n, param->base) + 1)
			ft_putchar_fd('0', fd);
		else if (param->base == 16 && param->upp == 1)
			ft_putstr_fd("0X", fd);
		else if (param->base == 16)
			ft_putstr_fd("0x", fd);
	}
	return (printbase_help(n, fd, param, len));
}
