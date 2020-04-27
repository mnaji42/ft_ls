/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printbasell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaji <mnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 22:11:54 by mnaji             #+#    #+#             */
/*   Updated: 2019/11/13 20:21:29 by mnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	nbrlen_basell(unsigned long long int n, int base)
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

static int	accur_basell(unsigned long long int n, t_param *param)
{
	if (nbrlen_basell(n, param->base) < param->accur)
		return (param->accur);
	return (nbrlen_basell(n, param->base));
}

int			totallen_basell(unsigned long long int n, t_param *param)
{
	int		count;

	count = 0;
	if (param->flags.fcsharp == 1 && param->base == 8 && n != 0)
	{
		if (param->accur < nbrlen_basell(n, param->base) + 1)
			count++;
	}
	else if (param->flags.fcsharp == 1 && param->base != 10 && n != 0)
		count = 2;
	count = count + accur_basell(n, param);
	return (count);
}

static int	printbasell_help(unsigned long long int n, int fd, \
		t_param *param, int len)
{
	int		tmp;

	if (param->width > nbrlen_basell(n, param->base) && \
			param->flags.fminus == 0)
		while (param->width-- > totallen_basell(n, param))
		{
			ft_putchar_fd('0', fd);
			len++;
		}
	tmp = param->accur;
	while (tmp-- > nbrlen_basell(n, param->base))
		ft_putchar_fd('0', fd);
	if (!(n == 0 && param->accur == 0 && param->flags.fcsharp == 0) \
			&& param->base != 16)
		len = len + printbase2ll_fd(n, fd, param);
	else if (!(n == 0 && param->accur == 0) && param->base == 16)
		len = len + printbase2ll_fd(n, fd, param);
	if (param->width > totallen_basell(n, param) && param->flags.fminus == 1)
		while (param->width-- > totallen_basell(n, param))
		{
			ft_putchar_fd(' ', fd);
			len++;
		}
	return (len);
}

int			printbasell_fd(unsigned long long int n, int fd, t_param *param)
{
	int		len;

	len = 0;
	if (n == 0 && param->accur == 0)
		param->width++;
	if (param->width > totallen_basell(n, param) && param->flags.fminus == 0 \
			&& (param->flags.f0 == 0 || param->accur != -1))
		while (param->width-- > totallen_basell(n, param))
		{
			ft_putchar_fd(' ', fd);
			len++;
		}
	if (param->flags.fcsharp == 1 && n != 0)
	{
		if (param->base == 2)
			ft_putstr_fd("0b", fd);
		else if (param->base == 8 && param->accur < \
				nbrlen_basell(n, param->base) + 1)
			ft_putchar_fd('0', fd);
		else if (param->base == 16 && param->upp == 1)
			ft_putstr_fd("0X", fd);
		else if (param->base == 16)
			ft_putstr_fd("0x", fd);
	}
	return (printbasell_help(n, fd, param, len));
}
