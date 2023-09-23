/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doduwole <doduwole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 10:20:42 by doduwole          #+#    #+#             */
/*   Updated: 2023/09/23 11:21:39 by doduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

static int	simulation(t_philo *phi)
{
	if (!philo_eat(phi))
		return (0);
	if (phi->n_eaten != phi->data->n_eat)
	{
		if (!philo_sleep(phi))
			return (0);
		if (!philo_think(phi))
			return (0);
	}
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*phi;

	phi = arg;
	if (phi->data->n_eat > 0)
		routine_refill(phi);
	else
		routine_hungry(phi);
	return (NULL);
}

void	routine_refill(t_philo *phi)
{
	while (1)
	{
		pthread_mutex_lock(&phi->data->shared);
		if ((phi->data->n_eat > phi->n_eaten) && !phi->data->philo_died)
		{
			pthread_mutex_unlock(&phi->data->shared);
			simulation(phi);
		}
		else
		{
			pthread_mutex_unlock(&phi->data->shared);
			break ;
		}
	}
}

void	routine_hungry(t_philo *phi)
{
	while (1)
	{
		pthread_mutex_lock(&phi->data->shared);
		if (!phi->data->philo_died)
		{
			pthread_mutex_unlock(&phi->data->shared);
			if (!simulation(phi))
				break ;
		}
		else
		{
			pthread_mutex_unlock(&phi->data->shared);
			break ;
		}
	}
}