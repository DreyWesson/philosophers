/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doduwole <doduwole@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 19:14:44 by doduwole          #+#    #+#             */
/*   Updated: 2023/09/23 12:10:52 by doduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	handle_thread(t_philo *phi)
{
	int	i;

	i = 0;
	if (!init_mutex_two(phi, &i))
		return (1);
	usleep(2000);
	phi->data->timer = get_time();
	while (i < phi->data->philo_num)
	{
		if (pthread_create(&phi[i].th, NULL, routine, &phi[i]))
			return (ft_error("Failed to create thread"), 0);
		i++;
		usleep(2000);
	}
	i = -1;
	while (++i < phi->data->philo_num)
		if (pthread_join(phi[i].th, NULL))
			return (ft_error("Failed to join thread"), 0);
	if (pthread_join(phi->data->monitor, NULL))
		return (ft_error("Failed to join thread"), 0);
	return (1);
}
