/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   two.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doduwole <doduwole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 10:20:23 by doduwole          #+#    #+#             */
/*   Updated: 2023/09/23 10:33:23 by doduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

void	routine_two_refill(t_philo *phi)
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

void	routine_two_hungry(t_philo *phi)
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

void	*routine_two(void *args)
{
	t_philo	*phi;

	phi = args;
	if (phi->data->n_eat > 0)
		routine_two_refill(phi);
	else
		routine_two_hungry(phi);
	return (NULL);
}
