/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doduwole <doduwole@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 19:18:16 by doduwole          #+#    #+#             */
/*   Updated: 2023/09/23 08:15:47 by doduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	routine2_helper1(t_philo *phi)
{
	int	i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&phi->data->shared);
		if (phi[i].data->n_eat > phi[i].n_eaten && !phi[i].data->philo_died)
		{
			pthread_mutex_unlock(&phi->data->shared);
			if (is_dead(phi, &i))
				break ;
		}
		else
		{
			pthread_mutex_unlock(&phi->data->shared);
			break ;
		}
	}
}

void	routine2_helper2(t_philo *phi)
{
	int	i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&phi->data->shared);
		if (!phi[i].data->philo_died)
		{
			pthread_mutex_unlock(&phi->data->shared);
			if (is_dead(phi, &i))
				break ;
		}
		else
		{
			pthread_mutex_unlock(&phi->data->shared);
			break ;
		}
	}
}

void	routine_helper1(t_philo *phi)
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

void	routine_helper2(t_philo *phi)
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
