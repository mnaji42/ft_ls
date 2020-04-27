/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_csp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaji <mnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 21:46:54 by mnaji             #+#    #+#             */
/*   Updated: 2019/11/13 18:22:08 by mnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		printstr_help(char const *str, int fd, t_param *param, int malloc)
{
	int		tmp;

	tmp = param->width;
	if (tmp > ft_strlen(str) && param->flags.fminus == 0)
		while (tmp-- > ft_strlen(str))
			ft_putchar_fd(' ', fd);
	ft_putstr_fd(str, fd);
	if (tmp > ft_strlen(str) && param->flags.fminus == 1)
		while (tmp-- > ft_strlen(str))
			ft_putchar_fd(' ', fd);
	if (malloc == 1)
		ft_strdel(str);
	if (param->width > ft_strlen(str))
		return (param->width);
	return (ft_strlen(str));
}

int		printstr_fd(char const *str, int fd, t_param *param)
{
	int		tmp;
	int		malloc;

	tmp = param->width;
	malloc = 0;
	if (!str)
	{
		str = ft_strdup("(null)");
		malloc = 1;
	}
	if (param->accur == -1 || param->accur >= ft_strlen(str))
		return (printstr_help(str, fd, param, malloc));
	if (tmp > param->accur && param->flags.fminus == 0)
		while (tmp-- > param->accur)
			ft_putchar_fd(' ', fd);
	ft_printnc_fd(str, param->accur, fd);
	if (tmp > param->accur && param->flags.fminus == 1)
		while (tmp-- > param->accur)
			ft_putchar_fd(' ', fd);
	if (malloc == 1)
		ft_strdel(str);
	return (param->width > param->accur ? param->width : param->accur);
}

int		printchar_fd(int c, int fd, t_param *param)
{
	int		len;

	len = 1;
	if (param->width > 1 && param->flags.fminus == 0 && param->flags.f0 == 1)
		while (param->width-- > 1)
		{
			ft_putchar_fd('0', fd);
			len++;
		}
	else if (param->width > 1 && param->flags.fminus == 0)
		while (param->width-- > 1)
		{
			ft_putchar_fd(' ', fd);
			len++;
		}
	ft_putchar_fd(c, fd);
	if (param->width > 1 && param->flags.fminus == 1)
		while (param->width-- > 1)
		{
			ft_putchar_fd(' ', fd);
			len++;
		}
	return (len);
}

int		printptr_fd(unsigned long long int ptr, int fd, t_param *param)
{
	int		len;
	int		ptrlen;

	len = 0;
	ptrlen = 14;
	if (!ptr)
		ptrlen = 3;
	if (param->width > ptrlen && param->flags.fminus == 0)
		while (param->width-- > ptrlen)
		{
			ft_putchar_fd(' ', fd);
			len++;
		}
	if (ptr)
		len = len + ft_printf("%#llx", ptr);
	else
		len = len + ft_printf("0x0");
	if (param->width > ptrlen && param->flags.fminus == 1)
		while (param->width-- > ptrlen)
		{
			ft_putchar_fd(' ', fd);
			len++;
		}
	return (len);
}
