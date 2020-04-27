/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaji <mnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 03:12:13 by mnaji             #+#    #+#             */
/*   Updated: 2019/11/12 01:32:22 by mnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>

void					ft_putchar(char c);
void					ft_putstr(char const *s);
void					ft_putstr_fd(char const *s, int fd);
void					ft_putchar_fd(char c, int fd);
int						ft_strlen(const char *s);
int						ft_printstr(const char *s);
char					*ft_strchr(const char *s, int c);
void					ft_bzero(void *s, int n);
void					ft_putnbr_fd(int n, int fd);
int						ft_atoi(const char *nptr);
void					ft_printnc_fd(const char *str, int n, int fd);
unsigned long long int	ft_powerof_10(int pow);
char					*ft_strdup(const char *s);
void					ft_strdel(const char *str);

#endif
