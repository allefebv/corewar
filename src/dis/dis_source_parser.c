/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dis_source_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mndhlovu <mndhlovu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 04:18:40 by mndhlovu          #+#    #+#             */
/*   Updated: 2019/07/02 12:05:00 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int				dis_verify_magic(int fd)
{
	unsigned int		magic;

	if ((read(fd, &magic, sizeof(unsigned int))) < 0)
		return (0);
	magic = dis_endian_conversion(magic);
	if (magic == (unsigned int)COREWAR_EXEC_MAGIC)
		return (fd);
	return (0);
}

static unsigned int		dis_save_prog_size(int *fd)
{
	unsigned int		prog_size;

	if ((read(*fd, &prog_size, sizeof(unsigned int))) < 0)
		return (0);
	prog_size = dis_endian_conversion(prog_size);
	return (prog_size);
}

static void				dis_pri_processor(char *file, int pv_number
						, t_file *champ, t_dis_game *game)
{
	char				*tmp;
	char				*str;

	tmp = ft_strndup(file, ft_strlen(file) - 4);
	if (!(str = ft_strjoin(tmp, ".s")))
	{
		ft_strdel(&tmp);
		return ;
	}
	ft_strdel(&tmp);
	champ->output_file = str;
	champ->file_name = file;
	champ->instr_nodes = NULL;
	champ->dis_state = 0;
	champ->col = pv_number;
	game->file[pv_number] = champ;
	(game->pv_number)++;
	(game->nbr_champs)++;
}

int						dis_source_parser(int fd, char *file
						, t_dis_game *game)
{
	t_file			*new;

	if (game->pv_number < MAX_PLAYERS)
	{
		if (!(new = (t_file *)malloc(sizeof(t_file))))
			return (-2);
		if (!(fd = dis_verify_magic(fd)))
			return (-1);
		if ((read(fd, new->name
						, sizeof(unsigned char) * PROG_NAME_LENGTH)) < 0)
			return (-2);
		if ((lseek(fd, 136, SEEK_SET)) < 0)
			return (-2);
		if (!(new->prog_size = dis_save_prog_size(&fd)))
			return (-2);
		if ((read(fd, new->comment
						, sizeof(unsigned char) * COMMENT_LENGTH)) < 0)
			return (-2);
		new->fd = fd;
		dis_pri_processor(file, game->pv_number, new, game);
		return (1);
	}
	return (-4);
}
