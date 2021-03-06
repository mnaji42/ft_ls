/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnc_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaji <mnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 00:02:45 by mnaji             #+#    #+#             */
/*   Updated: 2019/11/12 01:13:00 by mnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printnc_fd(const char *str, int n, int fd)
{
	int		i;

	i = 0;
	while (i < n)
		ft_putchar_fd(str[i++], fd);
}
