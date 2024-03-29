/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dis_error_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mndhlovu <mndhlovu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 04:19:07 by mndhlovu          #+#    #+#             */
/*   Updated: 2019/07/02 12:45:56 by mndhlovu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static char const	*g_usage[] =
{
	"Usage:./disassembly [-debug] [-v] <champion1.cor> <...>",
	"### CONTESTANT ######################################################",
	"your_champion.cor: Champion compiled with the asm",
	"### TEXT OUTPUT MODE ################################################",
	"-debug:            Text Debug Mode",
	"-v:            Ncurses Visualizer Mode",
	"#####################################################################"
};

int						dis_catch_error(int flag, char *av)
{
	int					index;

	index = 0;
	if (flag == US_ERROR)
	{
		while (index < (int)(sizeof(g_usage) / sizeof(g_usage[0])))
			ft_printf("%s%s\n", CLR_GREEN, g_usage[index++]);
		ft_printf("%s", KWTH);
	}
	else if (flag == IO_ERROR)
		ft_printf("%sCannot read source file %s%s\n", CLR_RED, av, KWTH);
	else if (flag == OPT_ERROR)
		ft_printf("%sError found around %s%s\n", CLR_YEL, av, KWTH);
	else if (flag == -1)
		ft_printf("%sInvalid magic number found on %s%s\n", CLR_RED, av, KWTH);
	else if (flag == -2)
		ft_printf("%sIO error or malloc error on %s%s\n", CLR_RED, av, KWTH);
	else if (flag == -3)
		ft_printf("%sMalloc error %s to memory%s\n", CLR_RED, av, KWTH);
	else if (flag == -4)
		ft_printf("%sMAX players reached%s\n", CLR_RED, KWTH);
	return (0);
}
