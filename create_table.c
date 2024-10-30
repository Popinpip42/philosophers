#include "philosophers.h"

t_node  *create_node(int  *valid_args)
{
  t_node  *new_node;

  new_node = (t_node *)malloc(sizeof(t_node));
  if (!new_node)
    return (NULL);
  new_node->is_alive = 1;
  new_node->id = 0;
  new_node->time_to_die = valid_args[1];
  new_node->time_to_eat = valid_args[2];
  new_node->time_to_sleep = valid_args[3];
  new_node->times_to_eat = valid_args[4];
  new_node->next = new_node;
  return (new_node);
}

int add_node_back(t_node *head, t_node* new_node)
{
  t_node  *tmp;
  int     i;

  if (!new_node || !head)
    return (0);
  i = 1;
  tmp = head;
  while (tmp->next != head) //TODO: verify that tmp->next is not NULL
  {
    tmp = tmp->next;
    i++;
  }
  tmp->next = new_node;
  new_node->next = head;
  new_node->id = i;
  return (1);
}

void  clear_list(t_node *head)
{
  t_node  *current;
  t_node  *next;

  if (!head)
    return ;
  current = head;
  next = current->next;
  if (next == head)
  {
    free(current);
    return ;
  }
  while (next != head)
  {
    next = next->next;
    free(current);
    current = next;
  }
}

void  print_table(t_node *head)
{
  t_node  *current;

  current = head;
  printf("Id : %d, Is_alive : %d\n", current->id, current->is_alive);
  current = current->next;
  while (current != head)
  {
    printf("Id : %d, Is_alive : %d\n", current->id, current->is_alive);
    current = current->next;
  }
}

t_node  *create_table(int elements, int *valid_args)
{
  t_node  *head;
  int     i;

  if (elements <= 0) //TODO: Add restriction: (<= 200; <= 250)
    return (NULL);

  //i = 1;
  head = create_node(valid_args);
  if (!head)
    return (NULL);
  elements--;
  while (elements--)
  {
    if (!add_node_back(head, create_node(valid_args)))
      return (clear_list(head), NULL);
  }
  return (head);
}

