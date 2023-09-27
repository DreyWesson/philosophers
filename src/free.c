/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doduwole <doduwole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 11:25:35 by doduwole          #+#    #+#             */
/*   Updated: 2023/09/27 13:10:53 by doduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	free_all(t_data *data, t_philo *phi)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
		pthread_mutex_destroy(data->mymutex + i);
	i = 0;
	while (i < data->philo_num)
	{
		pthread_mutex_destroy(&phi[i].data->tm);
		pthread_mutex_destroy(&phi[i].data->shared);
		i++;
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->shared);
	pthread_mutex_destroy(&data->tm);
	free(data->mymutex);
	free(data);
	free(phi);
}

void	free_single(t_data *data, t_philo *phi)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
		pthread_mutex_destroy(data->mymutex + i);
	pthread_mutex_destroy(&data->print);
	free(data->mymutex);
	free(data);
	free(phi);
}
