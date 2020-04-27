/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaji <mnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 13:51:07 by mnaji             #+#    #+#             */
/*   Updated: 2019/11/13 15:15:19 by mnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

typedef struct	s_varfloat
{
	int						exp;
	unsigned long long int	integer;
	int						i;
	int						mod;
	int						di;
	unsigned char			*c;
	unsigned long long int	decimal;
}				t_varfloat;

typedef struct	s_flags
{
	int						fcsharp;
	int						f0;
	int						fspace;
	int						fplus;
	int						fminus;
}				t_flags;

typedef struct	s_param
{
	int						width;
	int						accur;
	int						size;
	int						base;
	int						upp;
	int						h;
	int						l;
	t_flags					flags;
}				t_param;

typedef struct	s_printf
{
	int						fd;
	unsigned long int		i;
	int						len;
}				t_printf;

typedef struct	s_doublenorme
{
	int						len;
	double					db;
	unsigned long long int	integer;
	int						e;
}				t_doublenorme;

int				ft_printf(const char *format, ...);
void			print_convert(const char *str, t_printf *p, va_list args);
void			print_convert2(const char *str, t_printf *p, va_list args, \
					t_param param);
int				printnbr_fd(int n, int fd, t_param *param);
int				printnbrll_fd(long long int n, int fd, t_param *param);
int				printbase_fd(unsigned int n, int fd, t_param *param);
int				printbase2_fd(unsigned int n, int fd, t_param *param);
int				totallen_base(unsigned int n, t_param *param);
int				totallen_basell(unsigned long long int n, t_param *param);
int				printbase2ll_fd(unsigned long long int n, int fd, \
					t_param *param);
int				printbasell_fd(unsigned long long int n, int fd, \
					t_param *param);
int				printstr_fd(char const *str, int fd, t_param *param);
int				printchar_fd(int c, int fd, t_param *param);
int				printptr_fd(unsigned long long int ptr, int fd, t_param *param);
int				printdouble_fd(va_list args, int fd, t_param *param, char conv);
void			stock_integer(double db, unsigned long long int *stock);
void			printdouble_help1(char *conv, t_doublenorme *d, t_param *param);
int				printdouble_help2(char conv, t_doublenorme d, t_param *param, \
					int fd);
int				ft_nbrlen(int n, t_param *param);
int				accur_nbr(int n, t_param *param);
int				u_nbrlen(int n);
int				printnbr2_fd(int n, int fd);
int				ft_nbrlenll(long long int n, t_param *param);
int				accur_nbrll(long long int n, t_param *param);
int				u_nbrlenll(long long int n);
int				printnbr2ll_fd(long long int n, int fd);

#endif
