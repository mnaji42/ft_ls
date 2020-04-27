/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najimehdi <najimehdi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 14:13:53 by najimehdi         #+#    #+#             */
/*   Updated: 2020/04/27 16:57:26 by najimehdi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		go_to_front(t_lst_ls **lst)
{
	while ((*lst)->prv)
		*lst = (*lst)->prv;
}

void		sort_lstls(t_lst_ls *lst)
{
	t_lst_ls	*tmp;
	t_lst_ls	*tmp2;
	t_lst_ls	tmp3;

	tmp = lst;
	tmp2 = lst->next;
	while (tmp2)
	{
		if (ft_strcmp(tmp->read->d_name, tmp2->read->d_name) > 0)
		{
			tmp3.read = tmp->read;
			tmp->read = tmp2->read;
			tmp2->read = tmp3.read;
			go_to_front(&tmp);
		}
		else
			tmp = tmp->next;
		tmp2 = tmp->next;
	}
	go_to_front(&lst);
}

void		sort_lstls_r(t_lst_ls *lst)
{
	t_lst_ls	*tmp;
	t_lst_ls	*tmp2;
	t_lst_ls	tmp3;

	tmp = lst;
	tmp2 = lst->next;
	while (tmp2)
	{
		if (ft_strcmp(tmp->read->d_name, tmp2->read->d_name) < 0)
		{
			tmp3.read = tmp->read;
			tmp->read = tmp2->read;
			tmp2->read = tmp3.read;
			go_to_front(&tmp);
		}
		else
			tmp = tmp->next;
		tmp2 = tmp->next;
	}
	go_to_front(&lst);
}

void		sort_lstls_t(t_lst_ls *lst)
{
	t_sortlst	tmp;
	struct stat *buff;
	struct stat *buff2;

	tmp.one = lst;
	tmp.two = lst->next;
	while (tmp.two)
	{
		buff = get_stat(tmp.one->read->d_name);
		buff2 = get_stat(tmp.two->read->d_name);
		if (buff->ST_MTIME.tv_sec < buff2->ST_MTIME.tv_sec)
		{
			tmp.three.read = tmp.one->read;
			tmp.one->read = tmp.two->read;
			tmp.two->read = tmp.three.read;
			go_to_front(&tmp.one);
			tmp.two = tmp.one->next;
		}
		else
			tmp.one = tmp.one->next;
		tmp.two = tmp.one->next;
		free(buff);
		free(buff2);
	}
	go_to_front(&lst);
}

void		sort_lstls_t_r(t_lst_ls *lst)
{
	t_sortlst	tmp;
	struct stat *buff;
	struct stat *buff2;

	tmp.one = lst;
	tmp.two = lst->next;
	while (tmp.two)
	{
		buff = get_stat(tmp.one->read->d_name);
		buff2 = get_stat(tmp.two->read->d_name);
		if (buff->ST_MTIME.tv_sec > buff2->ST_MTIME.tv_sec)
		{
			tmp.three.read = tmp.one->read;
			tmp.one->read = tmp.two->read;
			tmp.two->read = tmp.three.read;
			go_to_front(&tmp.one);
			tmp.two = tmp.one->next;
		}
		else
			tmp.one = tmp.one->next;
		tmp.two = tmp.one->next;
		free(buff);
		free(buff2);
	}
	go_to_front(&lst);
}
