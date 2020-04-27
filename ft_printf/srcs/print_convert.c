/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_convert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaji <mnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 20:43:26 by mnaji             #+#    #+#             */
/*   Updated: 2019/11/13 15:14:22 by mnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	check_s_b(t_param *param, const char *str, unsigned long int *i)
{
	if (str[*i] == 'h')
	{
		*i = *i + 1;
		if (str[*i] == 'h')
			*i = *i + 1;
		param->h = 1;
	}
	else if (str[*i] == 'l')
	{
		*i = *i + 1;
		if (str[*i] == 'l')
			*i = *i + 1;
		param->l = 1;
	}
	if (str[*i] == 'o')
		param->base = 8;
	else if (str[*i] == 'u')
		param->base = 10;
	else if (str[*i] == 'x' || str[*i] == 'X')
		param->base = 16;
	else if (str[*i] == 'b')
		param->base = 2;
	if (str[*i] == 'X')
		param->upp = 1;
}

static void	check_flags(t_param *param, const char *str, unsigned long int *i)
{
	if (str[*i] == '0')
		param->flags.f0 = 1;
	else if (str[*i] == '#')
		param->flags.fcsharp = 1;
	else if (str[*i] == ' ')
		param->flags.fspace = 1;
	else if (str[*i] == '-')
		param->flags.fminus = 1;
	else if (str[*i] == '+')
		param->flags.fplus = 1;
	*i = *i + 1;
}

static void	check_width(t_param *param, const char *str, unsigned long int *i, \
		va_list args)
{
	int		star;

	if (str[*i] == '*')
	{
		star = va_arg(args, int);
		if (star < 0)
		{
			param->flags.fminus = 1;
			star = -star;
		}
		param->width = star;
		*i = *i + 1;
	}
	else if (str[*i] > '0' && str[*i] <= '9')
	{
		param->width = ft_atoi(&str[*i]);
		while (str[*i] >= '0' && str[*i] <= '9')
			*i = *i + 1;
	}
}

static void	check_param(t_param *param, const char *str, unsigned long int *i, \
		va_list args)
{
	*i = *i + 1;
	param->width = -1;
	param->accur = -1;
	while (str[*i] == '0' || str[*i] == '#' || str[*i] == ' ' || \
			str[*i] == '-' || str[*i] == '+')
		check_flags(param, str, i);
	check_width(param, str, i, args);
	if (str[*i] == '.')
	{
		*i = *i + 1;
		if (str[*i] == '*')
		{
			if ((param->accur = va_arg(args, int)) < 0)
				param->accur = -1;
			*i = *i + 1;
		}
		else
		{
			param->accur = ft_atoi(&str[*i]);
			while (str[*i] >= '0' && str[*i] <= '9')
				*i = *i + 1;
		}
	}
	check_s_b(param, str, i);
}

void		print_convert(const char *str, t_printf *p, va_list args)
{
	t_param	param;

	ft_bzero(&param, sizeof(t_param));
	check_param(&param, str, &p->i, args);
	if (str[p->i] == 'F' && str[p->i + 1] == 'D')
	{
		p->fd = va_arg(args, int);
		p->i = p->i + 1;
	}
	else
		print_convert2(str, p, args, param);
}
