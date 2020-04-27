/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaji <mnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 20:39:08 by mnaji             #+#    #+#             */
/*   Updated: 2019/11/13 15:14:53 by mnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_convert2(const char *str, t_printf *p, va_list args, \
		t_param param)
{
	if (str[p->i] == '%')
		p->len += printchar_fd('%', p->fd, &param);
	else if (str[p->i] == 'c')
		p->len += printchar_fd(va_arg(args, int), p->fd, &param);
	else if (str[p->i] == 's')
		p->len += printstr_fd(va_arg(args, char const*), p->fd, &param);
	else if (str[p->i] == 'p')
		p->len += printptr_fd(va_arg(args, unsigned long long int), \
				p->fd, &param);
	else if ((str[p->i] == 'd' || str[p->i] == 'i') && param.l == 1)
		p->len += printnbrll_fd(va_arg(args, long long int), p->fd, &param);
	else if (str[p->i] == 'd' || str[p->i] == 'i')
		p->len += printnbr_fd(va_arg(args, int), p->fd, &param);
	else if (param.l == 1)
		p->len += printbasell_fd(va_arg(args, unsigned long long int), \
				p->fd, &param);
	else if (str[p->i] == 'o' || str[p->i] == 'u' || str[p->i] == 'x' || \
			str[p->i] == 'X' || str[p->i] == 'b')
		p->len += printbase_fd(va_arg(args, unsigned int), p->fd, &param);
	else if (str[p->i] == 'f' || str[p->i] == 'e' || str[p->i] == 'g' || \
			str[p->i] == 'G' || str[p->i] == 'E')
		p->len += printdouble_fd(args, p->fd, &param, str[p->i]);
}

int		ft_printf(const char *format, ...)
{
	t_printf	printf;
	va_list		args;

	printf.i = -1;
	printf.len = 0;
	printf.fd = 1;
	va_start(args, format);
	while (format[++printf.i] != '\0')
	{
		if (format[printf.i] == '%')
			print_convert(format, &printf, args);
		else
		{
			ft_putchar_fd(format[printf.i], printf.fd);
			printf.len++;
		}
	}
	va_end(args);
	return (printf.len);
}
