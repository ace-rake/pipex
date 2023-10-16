/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:32:55 by vdenisse          #+#    #+#             */
/*   Updated: 2023/10/16 12:52:02 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	exit_handler(int cust_errno, t_data *data)
{
	if (data)
		delete_tmp_files(data);
	if (data)
		free_data(data);
	if (cust_errno == 0)
		if (errno != 0)
			perror("error");
	if (cust_errno == 1)
		perror("execute");
	if (cust_errno == 2)
		perror("no commands given");
	if (cust_errno == 3)
		perror("data_init");
	exit(errno);
}
