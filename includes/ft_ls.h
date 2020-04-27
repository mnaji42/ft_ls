/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najimehdi <najimehdi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 23:52:50 by najimehdi         #+#    #+#             */
/*   Updated: 2020/04/27 16:56:53 by najimehdi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include "ft_printf.h"
# include <stdio.h>
# include <errno.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/stat.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>

# if __APPLE__
#  define ST_MTIME st_mtimespec
# elif __linux__
#  define ST_MTIME st_mtim
# elif __unix__
#  define ST_MTIME st_mtim
# else
#  error "Unknown compiler"
# endif

# define NB_FLAGS 14
# define MAX_PATHS 100

/*
**	-C(done) Présenter les fichiers en colonnes, triés verticalement. (done)
**	-F(done) Ajouter un caractère à chaque nom de fichier pour indiquer
**		son type. les fichiers réguliers exécutables sont suivis
**		d'un « * ». Les répertoires sont suivis de « / », les liens
**		symboliques d'un « @ », les FIFOs d'un « | ». Les fichiers
**		réguliers non-exécutables ne sont suivis d'aucun caractère.
**	-R Afficher récursivement le contenu des sous-répertoires.
**	-a(done) Afficher tous les fichiers des répertoires, y compris les
**	  	fichiers commençant par un « . ».
**	-c(done) Employer la date de changement de statut des fichiers plutôt
**		que la date de modification, autant pour l'affichage (option -l)
**		que pour le tri (option -t).
**	-d(a voir) Afficher les répertoires avec la même présentation que les
**		fichiers, sans lister leur contenu. (done à voir)
**	-i(done) Afficher le numéro d'index (i-noeud) de chaque fichier à gauche de
**		son nom.
**	-l (done) En plus du nom, afficher le type du fichier, les permissions
**		d'accès, le nombre de liens physiques, le nom du propriétaire et du
**		groupe, la taille en octets, et l'horodatage. La ligne de résumé utilise
**		des unités de 512 octets. Les types de fichiers sont indiqués par les c
**		aractères suivants : - pour les fichiers ordinaires, d pour un
**		répertoire (directory), b pour un fichier spécial en mode bloc, c
**		pour un fichier spécial en mode caractère, l pour un lien symbolique,
**		p pour une fifo (named pipe), s pour une socket. Par défaut,
**		l'horodatage présenté est celui de la dernière modification du fichier.
**		Les options -c et -u réclament les autres horodatages. Pour les
**		fichiers spéciaux, le champ de taille est généralement remplacé par
**		les numéros majeur et mineur du périphérique.
**	-q(done) Afficher des points d'interrogation à la place des caractères
**		non-imprimables dans les noms de fichiers. Il est possible que cela
**		soit le cas par défaut lorsque la sortie standard est un terminal.
**	-r(done) Inverser le tri du contenu des répertoires.
**	-t(done) Trier le contenu des répertoires en fonction de la date et non pas
**		en ordre alphabétique. Les fichiers les plus récents sont présentés
**		en premier.
**	-u(done) Employer la date des derniers accès aux fichiers plutôt que la date
**		de modification, autant pour l'affichage (option -l) que pour le
**		tri (option -t).
**	-1(done) Présenter un fichier par ligne.
**	--(done) Indique la fin explicite des options.
*/

/*
**	MANDATORY done :
**		-r
**		-t
**		-a
**		-l
*/

/*
**	BONUS done:
**		-C
**		-c
**		-u
**		--
**		-1
**		-F
**		-q
**		-i
**		color
*/

typedef enum
{
	f_l,
	f_R,
	f_a,
	f_r,
	f_t,
	f_F,
	f_C,
	f_c,
	f_i,
	f_q,
	f_u,
	f_O,
	f_b
}	t_flag;

typedef struct	s_ls
{
	t_bool		flags[NB_FLAGS];
	char		*paths[MAX_PATHS];
	int			nb_paths;
}				t_ls;

int				display_path(char *path, t_bool *fl, int recur);
void			display(struct dirent *read, t_bool *fl, char *path);

/*
** UTILS
*/

struct stat		*get_stat(char *name);
void			print_content(char *name, t_bool *fl);

/*
** LIST
*/

typedef struct	s_lst_ls
{
	char			*path;
	struct dirent	*read;
	struct s_lst_ls	*next;
	struct s_lst_ls	*prv;
}				t_lst_ls;

typedef struct	s_sortlst
{
	t_lst_ls	*one;
	t_lst_ls	*two;
	t_lst_ls	three;
}				t_sortlst;

t_lst_ls		*init_listls(void);
int				isempty_lstls(t_lst_ls *lst);
void			add_node(t_lst_ls *lst, struct dirent *read);
void			clear_lstls(t_lst_ls *lst);
void			print_lstls(t_lst_ls *lst);
void			go_to_front(t_lst_ls **lst);
void			sort_lstls(t_lst_ls *lst);
void			sort_lstls_r(t_lst_ls *lst);
void			sort_lstls_t(t_lst_ls *lst);
void			sort_lstls_t_r(t_lst_ls *lst);
void			sort_content(t_lst_ls *lst, t_bool *fl);

#endif
