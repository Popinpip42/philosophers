#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h> //Currently using for isspace()
# include <limits.h> //Currently using for INT_MAX/MIN
# include <sys/time.h> //gettimeofday()
# include <unistd.h> //usleep()

typedef int (*t_validation_func)(const char *);
typedef int (*t_is_separator)(int);
typedef int (*t_filter_func)(int, int *, int);

typedef struct s_table
{
  int             n_philos;
  long            start_time;
  int             *state_table;
  int             *queue;
  int             queue_size; //TODO: must be thread safe
  int             deaths_count;
  int             completed_count;
  pthread_mutex_t deaths_mutex;
  pthread_mutex_t completed_mutex;
  pthread_mutex_t print_mutex;
  pthread_mutex_t queue_mutex;
  pthread_mutex_t queue_mutex2;
} t_table;

typedef struct s_node
{
  int             is_alive;
  int             id;
  long            last_meal_time;
  int             time_to_die;
  int             time_to_eat;
  int             time_to_sleep;
  int             times_to_eat; //This value is set to (-1) if 5th arg is not defined, we run simulation infinetly
  pthread_mutex_t fork_mutex;
  t_table         *table;
  struct s_node   *next;
} t_node;

//Simulation Functions
long  get_time_ms();
void  run_simulation(t_node *head, t_table *table);

//Core Functions
//t_node  *create_table(int elements, int *valid_args, t_table *table);
t_node  *create_table(int elements, int *valid_args, int args_len, t_table *table);
t_table *init_table(int n_philos);
void    clear_table(t_table **table);

//List Functions
void    print_node(t_node *node);
void    clear_list(t_node **head);
void    print_table(t_node *head);

//Validation
//int *validate_argv(int argc, char **argv, t_validation_func validate);
int *validate_argv(int argc, char **argv, t_validation_func validate, int *len);

//Validation Func
int is_overflowing(long result, int digit, int sign);
//int is_valid_int(const char *str);
int is_valid_pos_int(const char *str);

//Split_on
int   count_words(const char *s, t_is_separator is_separator);
char  *get_word(const char *s, t_is_separator is_separator);
char  **clean_matrix(char **matrix);
char  **split_on(const char *s, t_is_separator is_separator);

//Strings
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
int	ft_atoi(const char *str);

//AUXILIAR_FOR DEBUGGING
void  print_int_arr(int *arr, int len);

#endif
