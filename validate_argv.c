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
    else
      printf("-- Error on args %s\n", split_arg[i]);
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

int *validate_argv(int argc, char **argv, t_validation_func validate)
{
  int *valid_args;
  int valid_args_len;
  //TODO: see if there is at least 5
  //since 5th is optional

  valid_args_len = count_valid_args(argc, argv, validate);
  printf("valid_args_len : %d\n", valid_args_len);
  if (valid_args_len == 4)
  {
    //RUN INFINETLY
  }
  else if (valid_args_len == 5)
  {
    //RUN a limited amount of times according to 5th arg
  }
  else{
    //Invalid amount of valid_args_len, RETURN (NULL);
    return (NULL);
  }
  //valid_args = (int *)malloc(valid_args_len * sizeof(int));
  return (valid_args);
}
