/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mndhlovu <mndhlovu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 19:45:05 by mndhlovu          #+#    #+#             */
/*   Updated: 2019/05/29 09:46:57 by mndhlovu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int				main(int ac, char **av)
{
	int			fd;
	int			ret;
	int			index;
	char		buff[4028];
	
	index = 0;
	fd = open(av[1], O_RDONLY, 0);
	ret = lseek(fd, 128, SEEK_SET);
	printf("ret fseek: %d\n", ret);
	while(read(fd, buff, 4000))
		index++;
	printf("index: %d\n", index);
	index = 0;
	printf("%x \n", buff[0])
	return (0);
}


