/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:32:55 by vdenisse          #+#    #+#             */
/*   Updated: 2023/08/30 15:17:15 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void exit_handler(int cust_errno, t_data *data)
{
	if (data)
		free_data(data);
	if (cust_errno == 0)
		if (errno != 0)
		{
			perror("error");
			exit(errno);
		}
	if	(cust_errno == 1)
	{
		perror("invalid command arguments");
		exit(errno);
	}
}
