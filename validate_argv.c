#include "philosophers.h"

int count_arg(char *arg, t_validation_func validate)
{
  int   count;
  int   i;
  char  **split_arg;

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

int count_valid_args(int argc, char **argv, t_validation_func validate)
{
  int total_count;
  int num;
  int i;

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

int validate_and_get(char *arg, int *arr, t_validation_func validate)
{
  char  **split_arg;
  int   count;
  int   i;

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
      printf("-- Error on args %s\n", split_arg[i]);
    i++;
  }
  clean_matrix(split_arg);
  return (count);
}

int *validate_argv(int argc, char **argv, t_validation_func validate, int *len)
{
  int *valid_args;
  int valid_args_len;
  int i;
  int items_added;
  int ret_value;

  valid_args_len = count_valid_args(argc, argv, validate);
  if (valid_args_len == -1)
    return (printf("Malloc error1\n"), NULL);
  valid_args = (int *)malloc(valid_args_len * sizeof(int));
  if (!valid_args)
    return (printf("malloc error2\n"), NULL);
  items_added = 0;
  i = 1;
  while (i < argc)
  {
    ret_value = validate_and_get(argv[i], valid_args + items_added, validate);
    if (ret_value == -1)
      return (free(valid_args), NULL);
    items_added += ret_value;
    i++;
  }
  *len = valid_args_len;
  return (valid_args);
}
