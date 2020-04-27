/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_content.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najimehdi <najimehdi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 16:50:53 by najimehdi         #+#    #+#             */
/*   Updated: 2020/04/27 16:54:19 by najimehdi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_permitions(mode_t mode)
{
	char		permis[11];
	const char	file_symbol[] = ".pc.d.b.-.l.s.";
	const char	per[] = "-rwxst";
	int			i;
	int			n;

	i = 1;
	n = 0;
	ft_bzero(permis, 10);
	permis[0] = file_symbol[mode >> 12];
	while (i < 9)
	{
		permis[i++] = per[((mode & (S_IRUSR >> n)) != 0) * 1];
		permis[i++] = per[((mode & (S_IWUSR >> n)) != 0) * 2];
		if (!(mode & S_IXUSR >> n) && (mode & (S_ISUID >> (n / 3))) != 0)
			permis[i] = i < 7 ? 'S' : 'T';
		else
			permis[i] = per[(((mode & (S_IXUSR >> n)) != 0) * 3)
						+ ((mode & (S_ISUID >> (n / 3))) != 0) * (1 + (i > 7))];
		i++;
		n += 3;
	}
	ft_printf("%s ", permis);
}

static char	*display_time(char *time)
{
	time[16] = 0;
	return (time);
}

static void	display_content_l(struct dirent *read, t_bool *fl, char *path)
{
	struct stat		*buff;
	struct passwd	*pass;
	struct group	*group;
	char			*str_tmp;

	str_tmp = read->d_name;
	if (path)
		str_tmp = ft_strjoin(path, read->d_name);
	buff = get_stat(str_tmp);
	pass = getpwuid(buff->st_uid);
	group = getgrgid(pass->pw_gid);
	print_permitions(buff->st_mode);
	ft_printf("%3d %s  %s %6d %s ", buff->st_nlink, pass->pw_name,\
		group->gr_name, buff->st_size, display_time(ctime(&buff->st_mtime)));
	print_content(read->d_name, fl);
	ft_putchar('\n');
	free(buff);
	if (path)
		ft_strdel(&str_tmp);
}

static void	display_content(struct dirent *read, t_bool *fl)
{
	static int	newligne = 0;

	newligne++;
	print_content(read->d_name, fl);
	if (fl[f_O] || newligne == 4 || (fl[f_i] && newligne == 3))
	{
		ft_putchar('\n');
		newligne = 0;
	}
}

void		display(struct dirent *read, t_bool *fl, char *path)
{
	char		*str_tmp;
	struct stat	buff;

	str_tmp = ft_strjoin(path, read->d_name);
	if (stat(str_tmp, &buff) != -1)
	{
		if (fl[f_i])
			ft_printf("%d ", read->d_ino);
		if (fl[f_l])
			display_content_l(read, fl, path);
		else
			display_content(read, fl);
	}
	ft_strdel(&str_tmp);
}
