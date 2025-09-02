/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_argv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsirpa-g <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:40:46 by lsirpa-g          #+#    #+#             */
/*   Updated: 2025/09/02 12:40:46 by lsirpa-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	count_arg(char *arg, t_validation_func validate)
{
	int		count;
	int		i;
	char	**split_arg;

	split_arg = split_on(arg, &isspace);
	if (!split_arg)
		return (-1);
	count = 0;
	i = 0;
	while (split_arg[i] != NULL)
	{
		if (validate(split_arg[i]))
			count ++;
		i++;
	}
	clean_matrix(split_arg);
	return (count);
}

int	count_valid_args(int argc, char **argv, t_validation_func validate)
{
	int	total_count;
	int	num;
	int	i;

	total_count = 0;
	i = 1;
	while (i < argc)
	{
		num = count_arg(argv[i], validate);
		if (num == -1)
			return (-1);
		total_count += num;
		i++;
	}
	return (total_count);
}

int	validate_and_get(char *arg, int *arr, t_validation_func validate)
{
	char	**split_arg;
	int		count;
	int		i;

	split_arg = split_on(arg, &isspace);
	if (!split_arg)
		return (-1);
	count = 0;
	i = 0;
	while (split_arg[i] != NULL)
	{
		if (validate(split_arg[i]))
		{
			arr[count] = ft_atoi(split_arg[i]);
			count++;
		}
		else
			return (printf("--- Invalid argument %s\n", split_arg[i]), -1);
		i++;
	}
	clean_matrix(split_arg);
	return (count);
}

int	*validate_argv(int argc, char **argv, t_validation_func validate, int *len)
{
	int	*args;
	int	args_len;
	int	i;
	int	items_added;
	int	ret_value;

	args_len = count_valid_args(argc, argv, validate);
	if (args_len == -1)
		return (printf("Malloc error1\n"), NULL);
	args = (int *)malloc(args_len * sizeof(int));
	if (!args)
		return (printf("malloc error2\n"), NULL);
	items_added = 0;
	i = 1;
	while (i < argc)
	{
		ret_value = validate_and_get(argv[i], args + items_added, validate);
		if (ret_value == -1)
			return (free(args), NULL);
		items_added += ret_value;
		i++;
	}
	*len = args_len;
	return (args);
}
