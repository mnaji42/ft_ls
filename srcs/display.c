/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najimehdi <najimehdi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 16:48:29 by najimehdi         #+#    #+#             */
/*   Updated: 2020/04/27 16:54:08 by najimehdi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	return_size(char *path, struct dirent *read)
{
	char		*str_tmp;
	struct stat	*buff;
	int			ret;

	str_tmp = read->d_name;
	if (path)
		str_tmp = ft_strjoin(path, read->d_name);
	buff = get_stat(str_tmp);
	ret = buff->st_blocks;
	free(buff);
	if (path)
		ft_strdel(&str_tmp);
	return (ret);
}

static void	display_list(char *path, t_lst_ls *lst, t_bool *fl)
{
	t_lst_ls		*tmp;
	struct stat		*buff;
	char			*str_tmp;

	sort_lstls(lst);
	tmp = lst;
	while (tmp)
	{
		if (ft_strlen(tmp->read->d_name))
		{
			str_tmp = ft_strjoin(path, tmp->read->d_name);
			if (str_tmp[ft_strlen(str_tmp) - 1] != '/')
				str_tmp = ft_strjoin_free(str_tmp, str_tmp, "/");
			buff = get_stat(str_tmp);
			if (tmp->read->d_name[0] != '.' && S_ISDIR(buff->st_mode))
			{
				ft_printf("\n%s\n", str_tmp);
				display_path(str_tmp, fl, 1);
			}
			else
				ft_strdel(&str_tmp);
			free(buff);
		}
		tmp = tmp->next;
	}
}

static int	path_invalid(char *path, int recur)
{
	char			*error;

	if (recur)
	{
		ft_strdel(&path);
		return (1);
	}
	error = ft_strjoin_free(path, "ls : ", path);
	perror(error);
	ft_strdel(&error);
	return (1);
}

static void	display_contents(t_lst_ls *tmp, char *path, t_bool *fl, int total)
{
	if (fl[f_l])
		ft_printf("total %d\n", total);
	sort_content(tmp, fl);
	while (tmp)
	{
		if (!(!fl[f_a] && tmp->read->d_name[0] == '.')\
			&& ft_strlen(tmp->read->d_name))
			display(tmp->read, fl, path);
		tmp = tmp->next;
	}
}

int			display_path(char *path, t_bool *fl, int recur)
{
	DIR				*dir;
	struct dirent	*read;
	t_lst_ls		*lst;
	long int		total;

	total = 0;
	if (!(dir = opendir(path)))
		return (path_invalid(path, recur));
	lst = init_listls();
	while ((read = readdir(dir)))
	{
		total += return_size(path, read);
		add_node(lst, read);
	}
	display_contents(lst, path, fl, total);
	ft_putchar('\n');
	if (fl[f_R])
		display_list(path, lst, fl);
	ft_strdel(&path);
	closedir(dir);
	clear_lstls(lst);
	return (1);
}
