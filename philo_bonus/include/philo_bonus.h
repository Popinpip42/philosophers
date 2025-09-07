#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <ctype.h>
# include <limits.h>
# include <sys/time.h>

typedef int				(*t_validation_func)(const char *);
typedef int				(*t_is_separator)(int);
typedef int				(*t_filter_func)(int, int *, int);

typedef struct s_node	t_node;

typedef struct s_table
{
	int				n_philos;
	long			start_time;
	int				completed_count;
	int				simulation_state;
}	t_table;

struct s_node
{
	int				id;
	long			last_meal_time;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_to_eat;
	t_table			*table;
	t_node			*next;
};

// time.c
void		start_delay(long start_time);
long		get_time_ms(void);

// create_table.c
t_node		*create_table(int count, int *valid_args,
				int args_len, t_table *table);
void		clear_list(t_node **head);

// init_table.c
t_table		*init_table(int n_philos);
void		clear_table(t_table **table);

// validate_argv.c
int			*validate_argv(int argc, char **argv,
				t_validation_func validate, int *len);

// vallidate_func.c
int			is_valid_pos_int(const char *str);
int			ft_isdigit(int c);
int			ft_isspace(int c);

// strings.c
size_t		ft_strlen(const char *s);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
int			ft_atoi(const char *str);

// split_on.c
char		**split_on(const char *s, t_is_separator is_separator);
char		**clean_matrix(char **matrix);

#endif
