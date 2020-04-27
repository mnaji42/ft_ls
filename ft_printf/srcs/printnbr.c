/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printnbr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaji <mnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 23:28:59 by mnaji             #+#    #+#             */
/*   Updated: 2019/11/12 00:50:02 by mnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	printnbr_help2(int n, int fd, int *len)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		*len = *len + 1;
	}
}

static int	printnbr_help(int n, int fd, t_param *param, int len)
{
	int		tmp;

	printnbr_help2(n, fd, &len);
	if (param->width > ft_nbrlen(n, param) && param->flags.fminus == 0)
		while (param->width-- > ft_nbrlen(n, param))
		{
			ft_putchar_fd('0', fd);
			len++;
			param->accur--;
		}
	tmp = param->accur;
	while (tmp-- > u_nbrlen(n))
	{
		ft_putchar_fd('0', fd);
		len++;
	}
	if (!(n == 0 && param->accur == 0))
		len = len + printnbr2_fd(n, fd);
	if (param->width > accur_nbr(n, param) && param->flags.fminus == 1)
		while (param->width-- > accur_nbr(n, param))
		{
			ft_putchar_fd(' ', fd);
			len++;
		}
	return (len);
}

int			printnbr_fd(int n, int fd, t_param *param)
{
	int		len;

	len = 0;
	if (n == 0 && param->accur == 0)
		param->width++;
	if (param->width > accur_nbr(n, param) && param->flags.fminus == 0 && \
			(param->flags.f0 == 0 || param->accur != -1))
		while (param->width > accur_nbr(n, param))
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
	return (printnbr_help(n, fd, param, len));
}
