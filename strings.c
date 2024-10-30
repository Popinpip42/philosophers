#include "philosophers.h"

size_t	ft_strlen(const char *s)
{
	int	counter;

	counter = 0;
	while (s[counter])
		counter++;
	return (counter);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	int		len;
	size_t	i;

	len = ft_strlen(src);
	if (size == 0)
		return (len);
	i = 0;
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}

int	ft_atoi(const char *str)
{
	int	num;
	int	sign;

	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
  while (*str == '+' || *str == '-')
  {
    if (*str == '-')
      sign *= -1;
    str++;
  }
  num = 0;
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + (*str - '0');
		str++;
	}
	return (num * sign);
}
