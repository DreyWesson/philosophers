/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   two.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doduwole <doduwole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 10:20:23 by doduwole          #+#    #+#             */
/*   Updated: 2023/09/27 14:09:47 by doduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

void	routine_two_limited(t_philo *phi)
{
	int	i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&phi->data->shared);
		pthread_mutex_unlock(&phi->data->shared);
		if (phi[i].data->n_eat > phi[i].n_eaten && !phi[i].data->philo_died)
		{
			if (is_dead(phi, &i))
				break ;
		}
		else
			break ;
	}
}

void	routine_two_unlimited(t_philo *phi)
{
	int	i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&phi->data->shared);
		pthread_mutex_unlock(&phi->data->shared);
		if (!phi[i].data->philo_died)
		{
			if (is_dead(phi, &i))
				break ;
		}
		else
			break ;
	
	}
}

void	*routine_two(void *args)
{
	t_philo	*phi;

	phi = (t_philo *)args;
	if (phi->data->n_eat > 0)
		routine_two_limited(phi);
	else
		routine_two_unlimited(phi);
	return (NULL);
}
