/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:32:55 by vdenisse          #+#    #+#             */
/*   Updated: 2023/10/18 11:24:06 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	exit_handler(int cust_errno, t_data *data)
{
	printf("holla %d\n", errno);
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
	if (cust_errno == 4)
		perror("child_failure");
	exit(errno);
}
