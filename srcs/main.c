/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najimehdi <najimehdi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 00:02:07 by najimehdi         #+#    #+#             */
/*   Updated: 2020/04/27 16:51:25 by najimehdi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			add_flags_helps(t_bool *flags, char f)
{
	if (f == 'r')
		flags[f_r] = 1;
	else if (f == 'F')
		flags[f_F] = 1;
	else if (f == 'C')
		flags[f_l] = 0;
	else if (f == 'c')
		flags[f_c] = 1;
	else if (f == 'i')
		flags[f_i] = 1;
	else if (f == 'q')
		flags[f_q] = 1;
	else if (f == 'u')
		flags[f_u] = 1;
	else if (f == '1')
		flags[f_O] = 1;
	else if (f == 'b')
		flags[f_b] = 1;
	else if (f != '-')
	{
		ft_printf("ls: illegal option -- %c\n", f);
		ft_printf("usage: ls [-lRartFCciqu1b] [file ...]\n");
		return (0);
	}
	return (1);
}

int			add_flags(t_bool *flags, char *argv)
{
	int i;

	i = -1;
	while (argv[++i])
	{
		if (argv[i] == 'l')
			flags[f_l] = 1;
		else if (argv[i] == 'R')
			flags[f_R] = 1;
		else if (argv[i] == 'a')
			flags[f_a] = 1;
		else if (argv[i] == 't')
			flags[f_t] = 1;
		else if (!add_flags_helps(flags, argv[i]))
			return (0);
	}
	return (1);
}

int			check_argv(t_ls *ls, char **argv)
{
	int i;
	int i_paths;
	int no_more_flags;

	i = 0;
	i_paths = 0;
	no_more_flags = 0;
	while (argv[++i])
	{
		if (argv[i][0] == '-' && argv[i][1] == '-')
			no_more_flags = 1;
		else if (no_more_flags == 0 && argv[i][0] == '-')
		{
			if (!add_flags(ls->flags, argv[i]))
				return (0);
		}
		else
		{
			if (argv[i][ft_strlen(argv[i]) - 1] != '/')
				ls->paths[i_paths++] = ft_strjoin(argv[i], "/");
			else
				ls->paths[i_paths++] = ft_strdup(argv[i]);
		}
	}
	return (1);
}

int			main(int argc, char **argv)
{
	t_ls	ls;
	int		i;

	if (argc > MAX_PATHS + 1)
	{
		ft_printf("Too many argments\n");
		return (1);
	}
	i = 0;
	ft_bzero(&ls, sizeof(t_ls));
	if (!check_argv(&ls, argv))
		return (1);
	if (ls.paths[i] == NULL)
		display_path(ft_strdup("./"), ls.flags, 0);
	else
		while (ls.paths[i] != NULL)
			display_path(ls.paths[i++], ls.flags, 0);
	return (0);
}
