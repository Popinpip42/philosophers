#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h> //Currently using for isspace()
# include <limits.h> //Currently using for INT_MAX/MIN

typedef int (*t_validation_func)(const char *);
typedef int (*t_is_separator)(int);
typedef int (*t_filter_func)(int, int *, int);

typedef struct s_table{
  int shared_bowl;
  int n_philos;
} t_table;

typedef struct s_node
{
  int           is_alive;
  int           id;
  int           fork;
  int           time_to_die;
  int           time_to_eat;
  int           time_to_sleep;
  int           times_to_eat; //If (0) or (-1), we run simulation infinetly
  struct s_node *next;
} t_node;

//Core Functions
t_node  *create_table(int elements, int *valid_args);
t_table *init_table(int n_philos);

//List Functions
void    print_node(t_node *node);
void    clear_list(t_node **head);
void    print_table(t_node *head);

//Validation
//int *validate_argv(int argc, char **argv, t_validation_func validate);
int *validate_argv(int argc, char **argv, t_validation_func validate, int *len);

//Validation Func
int is_overflowing(long result, int digit, int sign);
int is_valid_int(const char *str);

//Split_on
int   count_words(const char *s, t_is_separator is_separator);
char  *get_word(const char *s, t_is_separator is_separator);
char  **clean_matrix(char **matrix);
char  **split_on(const char *s, t_is_separator is_separator);

//Strings
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
int	ft_atoi(const char *str);

#endif
