/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:30:24 by vdenisse          #+#    #+#             */
/*   Updated: 2023/10/18 13:30:54 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

char	*tmp_file_name_gen(int iter)
{
	char	*name;
	char	*nbr;

	nbr = ft_itoa(iter);
	name = ft_strjoin(TMP_FILE_NAME, nbr);
	free(nbr);
	return (name);
}

int	create_file(int iter)
{
	int		fd;
	char	*name;

	name = tmp_file_name_gen(iter);
	fd = open(name, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	free(name);
	return (fd);
}
