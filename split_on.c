#include "philosophers.h"

int count_words(const char *s, t_is_separator is_separator)
{
  int count = 0;
  int flag = 0;

  while (*s)
  {
    if (!is_separator((unsigned char)*s))
    {
      if (!flag)
      {
        count++;
        flag = 1;
      }
    }
    else
      flag = 0;
    s++;
  }
  return (count);
}

char *get_word(const char *s, t_is_separator is_separator)
{
  char *word;
  int size = 0;

  while (s[size] && !is_separator((unsigned char)s[size]))
    size++;
  word = (char *)malloc((size + 1) * sizeof(char));
  if (!word)
    return (NULL);
  ft_strlcpy(word, s, size + 1);
  return (word);
}

char **clean_matrix(char **matrix)
{
  int i;

  i = 0;
  while (matrix[i] != NULL)
  {
    free(matrix[i]);
    i++;
  }
  free(matrix);
  return (NULL);
}

char **split_on(const char *s, t_is_separator is_separator)
{
  char **matrix;
  int words_num;
  int row;

  words_num = count_words(s, is_separator);
  matrix = (char **)malloc((words_num + 1) * sizeof(char *));
  if (!matrix)
    return (NULL);
  row = 0;
  while (*s)
  {
    while (*s && is_separator((unsigned char)*s))
      s++;
    if (*s && !is_separator((unsigned char)*s))
    {
      matrix[row] = get_word(s, is_separator);
      if (!matrix[row])
        return (clean_matrix(matrix));
      row++;
      while (*s && !is_separator((unsigned char)*s))
        s++;
    }
  }
  matrix[row] = NULL;
  return (matrix);
}
