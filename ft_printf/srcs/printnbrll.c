/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printnbrll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaji <mnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 23:50:58 by mnaji             #+#    #+#             */
/*   Updated: 2019/11/12 00:50:20 by mnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	printnbrll_help2(long long int n, int fd, int *len)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		len++;
	}
}

static int	printnbrll_help(long long int n, int fd, t_param *param, int len)
{
	int		tmp;

	printnbrll_help2(n, fd, &len);
	if (param->width > ft_nbrlenll(n, param) && param->flags.fminus == 0)
		while (param->width-- > ft_nbrlenll(n, param))
		{
			ft_putchar_fd('0', fd);
			len++;
			param->accur--;
		}
	tmp = param->accur;
	while (tmp-- > u_nbrlenll(n))
	{
		ft_putchar_fd('0', fd);
		len++;
	}
	if (!(n == 0 && param->accur == 0))
		len = len + printnbr2ll_fd(n, fd);
	if (param->width > accur_nbrll(n, param) && param->flags.fminus == 1)
		while (param->width-- > accur_nbrll(n, param))
		{
			ft_putchar_fd(' ', fd);
			len++;
		}
	return (len);
}

int			printnbrll_fd(long long int n, int fd, t_param *param)
{
	int		len;

	len = 0;
	if (n == 0 && param->accur == 0)
		param->width++;
	if (param->width > accur_nbrll(n, param) && param->flags.fminus == 0 && \
			(param->flags.f0 == 0 || param->accur != -1))
		while (param->width > accur_nbrll(n, param))
		{
			ft_putchar_fd(' ', fd);
			param->width--;
			len++;
		}
	if (n >= 0 && param->flags.fplus == 1)
	{
		ft_putchar_fd('+', fd);
		len++;
	}
	else if (n >= 0 && param->flags.fspace == 1)
	{
		ft_putchar_fd(' ', fd);
		len++;
	}
	return (printnbrll_help(n, fd, param, len));
}
