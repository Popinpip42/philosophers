#include "philosophers.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int is_overflowing(long result, int digit, int sign)
{
  if (sign == 1 && result > (INT_MAX - digit) / 10)
    return (1);
  if (sign == -1 && result > ((-1L * INT_MIN) - digit) / 10)
    return (1);
  return (0);
}

int is_valid_pos_int(const char *str)
{
  long  result;
  int   sign;

  while (isspace(*str)) str++;
  sign = 1;
  while (*str == '-' || *str == '+')
  {
    if (*str == '-') sign *= -1;
    str++;
  }
  if (!ft_isdigit(*str)) return (0);
  result = 0;
  while (ft_isdigit(*str))
  {
    if (is_overflowing(result, (*str - '0'), sign))
      return (0);
    result = result * 10 + (*str - '0');
    str++;
  }
  if ((result * sign) <= 0) return (0);
  while (isspace(*str)) str++;
  return (*str == '\0');
}

