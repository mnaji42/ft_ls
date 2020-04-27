/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_base_help.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaji <mnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 21:55:38 by mnaji             #+#    #+#             */
/*   Updated: 2019/11/11 22:16:59 by mnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_down(unsigned int n, int fd)
{
	if (n % 16 == 15)
		ft_putchar_fd('f', fd);
	else if (n % 16 == 14)
		ft_putchar_fd('e', fd);
	else if (n % 16 == 13)
		ft_putchar_fd('d', fd);
	else if (n % 16 == 12)
		ft_putchar_fd('c', fd);
	else if (n % 16 == 11)
		ft_putchar_fd('b', fd);
	else if (n % 16 == 10)
		ft_putchar_fd('a', fd);
	else
		ft_putchar_fd((char)(n % 16 + 48), fd);
}

static void	print_up(unsigned int n, int fd)
{
	if (n % 16 == 15)
		ft_putchar_fd('F', fd);
	else if (n % 16 == 14)
		ft_putchar_fd('E', fd);
	else if (n % 16 == 13)
		ft_putchar_fd('D', fd);
	else if (n % 16 == 12)
		ft_putchar_fd('C', fd);
	else if (n % 16 == 11)
		ft_putchar_fd('B', fd);
	else if (n % 16 == 10)
		ft_putchar_fd('A', fd);
	else
		ft_putchar_fd((char)(n % 16 + 48), fd);
}

int			printbase2_fd(unsigned int n, int fd, t_param *param)
{
	if (n > (unsigned int)(param->base - 1))
		printbase2_fd(n / param->base, fd, param);
	if (param->base == 16 && param->upp == 1)
		print_up(n, fd);
	else if (param->base == 16)
		print_down(n, fd);
	else
		ft_putchar_fd((char)(n % param->base + 48), fd);
	return (totallen_base(n, param));
}

int			printbase2ll_fd(unsigned long long int n, int fd, t_param *param)
{
	if (n > (unsigned long long int)(param->base - 1))
		printbase2ll_fd(n / param->base, fd, param);
	if (param->base == 16 && param->upp == 1)
		print_up(n, fd);
	else if (param->base == 16)
		print_down(n, fd);
	else
		ft_putchar_fd((char)(n % param->base + 48), fd);
	return (totallen_basell(n, param));
}
