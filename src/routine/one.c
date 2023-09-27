/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doduwole <doduwole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 10:20:42 by doduwole          #+#    #+#             */
/*   Updated: 2023/09/27 14:09:10 by doduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

static int	simulation(t_philo *phi)
{
	if (!philo_eat(phi))
		return (0);
	if (phi->n_eaten != phi->data->n_eat)
	{
		if (!philo_sleep(phi) || !philo_think(phi))
			return (0);
	}
	return (1);
}

void	routine_limited(t_philo *phi)
{
	while (1)
	{
		pthread_mutex_lock(&phi->data->shared);
		pthread_mutex_unlock(&phi->data->shared);
		if ((phi->data->n_eat > phi->n_eaten) && !phi->data->philo_died)
			simulation(phi);
		else
			break ;
	}
}

void	routine_unlimited(t_philo *phi)
{
	while (1)
	{
		pthread_mutex_lock(&phi->data->shared);
		pthread_mutex_unlock(&phi->data->shared);
		if (!phi->data->philo_died)
		{			
			if (!simulation(phi))
				break ;
		}
		else
			break ;
	}
}

void	*routine(void *arg)
{
	t_philo	*phi;

	phi = (t_philo *)arg;
	if (phi->data->n_eat > 0)
		routine_limited(phi);
	else
		routine_unlimited(phi);
	return (NULL);
}
