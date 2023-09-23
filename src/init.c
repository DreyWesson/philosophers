/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doduwole <doduwole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:19:38 by doduwole          #+#    #+#             */
/*   Updated: 2023/09/23 11:12:19 by doduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_data(t_data *data, char **argv, int argc)
{
	data->philo_died = 0;
	data->philo_num = ft_atoi(argv[1]);
	data->time.to_die = ft_atoi(argv[2]);
	data->time.to_eat = ft_atoi(argv[3]);
	data->time.to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->n_eat = ft_atoi(argv[5]);
	else
		data->n_eat = -1;
	if (!data->philo_num || !data->time.to_die || !data->time.to_eat || !data->time.to_sleep
		|| (argc == 6 && !data->n_eat))
		return (ft_error("Some arguments are zero or out bound"), 0);
	return (1);
}

void	init_philo(t_philo *phi, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		phi[i].id = i;
		phi[i].n_eaten = 0;
		phi[i].t_die = 0;
		phi[i].hand.left = i;
		phi[i].hand.right = (i + 1) % data->philo_num;
		phi[i].data = data;
		i++;
	}
	phi[i].t_die = 0;
	phi[i].n_eaten = 0;
	phi[i].data = data;
}

int mutex_init(t_data *data)
{
	int i;
	
	i = 0;
	data->mymutex = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	if (!data->mymutex)
		return (ft_error("Memory allocation failed"), 0);
	while (i < data->philo_num)
		if (pthread_mutex_init(data->mymutex + i++, NULL))
			return (ft_error("Failed to initialise mutex"), 0);
	if (pthread_mutex_init(&data->print, NULL))
		return (ft_error("Failed to initialise mutex"), 0);
	return (1);
}

int init_mutex_two(t_philo *phi, int *i)
{

	if (pthread_mutex_init(&phi[*i].data->shared, NULL))
		return (ft_error("Failed to initialise mutex"), 0);
	if (pthread_mutex_init(&phi[*i].data->tm, NULL))
		return (ft_error("Failed to initialise mutex"), 0);
	if (pthread_create(&phi[0].data->monitor, NULL, routine_two, phi))
		return (ft_error("Failed to create thread"), 0);
	return (1);
}
