/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najimehdi <najimehdi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 00:19:43 by najimehdi         #+#    #+#             */
/*   Updated: 2020/04/27 14:22:01 by najimehdi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

struct stat	*get_stat(char *name)
{
	struct stat	*buff;
	char		*content;

	buff = (struct stat*)malloc(sizeof(struct stat));
	if (name[0] != '.')
		content = ft_strjoin("./", name);
	else
		content = ft_strdup(name);
	stat(content, buff);
	ft_strdel(&content);
	return (buff);
}

void		sort_content(t_lst_ls *lst, t_bool *fl)
{
	if (fl[f_t] && fl[f_r])
		sort_lstls_t_r(lst);
	else if (fl[f_t])
		sort_lstls_t(lst);
	else if (fl[f_r])
		sort_lstls_r(lst);
	else
		sort_lstls(lst);
}

static void	check_char(char *content)
{
	int		i;

	i = 0;
	while (content[i])
	{
		if (!ft_isprint(content[i]))
			content[i] = '?';
		i++;
	}
}

static void	print_content_help(char *name, t_bool *fl, \
						struct stat *buff, char *content)
{
	if (S_ISFIFO(buff->st_mode))
	{
		content = (fl[f_F]) ? ft_strjoin(name, "|") : ft_strdup(name);
		if (fl[f_q])
			check_char(content);
		ft_printf("\033[31m%-20s\033[0m", content);
	}
	else if (S_ISREG(buff->st_mode))
	{
		content = (fl[f_F]) ? ft_strjoin(name, "*") : ft_strdup(name);
		if (fl[f_q])
			check_char(content);
		ft_printf("\033[1m%-20s\033[0m", content);
	}
	else
	{
		content = ft_strdup(name);
		if (fl[f_q])
			check_char(content);
		ft_printf("%-20s", content);
	}
}

void		print_content(char *name, t_bool *fl)
{
	struct stat *buff;
	char		*content;

	buff = get_stat(name);
	content = NULL;
	if (S_ISDIR(buff->st_mode))
	{
		content = (fl[f_F]) ? ft_strjoin(name, "/") : ft_strdup(name);
		if (fl[f_q])
			check_char(content);
		ft_printf("\033[36m%-20s\033[0m", content);
	}
	else if (buff->st_mode == DT_LNK)
	{
		content = (fl[f_F]) ? ft_strjoin(name, "@") : ft_strdup(name);
		if (fl[f_q])
			check_char(content);
		ft_printf("\033[32m%-20s\033[0m", content);
	}
	else
		print_content_help(name, fl, buff, content);
	free(buff);
	ft_strdel(&content);
}
