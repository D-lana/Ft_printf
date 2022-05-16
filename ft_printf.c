#include "ft_printf.h"

static int	ft_argument_all(const char **symbol, va_list argument, t_list flags)
{
	int			score;
	const char	*symbol_2;

	symbol_2 = *symbol;
	score = 0;
	if (*symbol_2 == 'c' || *symbol_2 == 's')
		score = ft_argument_cs(&**symbol, &*argument, flags);
	else if (*symbol_2 == 'd' || *symbol_2 == 'i')
		score = ft_argument_di(&**symbol, &*argument, flags);
	else if (*symbol_2 == 'u')
		score = ft_argument_u(&**symbol, &*argument, flags);
	else if (*symbol_2 == 'x' || *symbol_2 == 'X' || *symbol_2 == 'p')
		score = ft_argument_xxp(&**symbol, &*argument, flags);
	else if (*symbol_2 == '%')
		score = ft_no_argument(&**symbol, flags);
	else
		return (0);
	symbol_2++;
	*symbol = symbol_2;
	return (score);
}

static int	ft_write_symbol(const char **symbol)
{
	const char	*symbol_2;

	symbol_2 = *symbol;
	if (*symbol_2 != '\0' && *symbol_2 != 37)
	{
		write (1, &*symbol_2, 1);
		symbol_2++;
		*symbol = symbol_2;
		return (1);
	}
	return (0);
}

static int	ft_write_percent(const char **symbol)
{
	const char	*symbol_2;

	symbol_2 = *symbol;
	write (1, &*symbol_2, 1);
	symbol_2++;
	*symbol = symbol_2;
	return (1);
}

int	ft_printf(const char *symbol, ...)
{
	t_list	flags;
	va_list	argument;
	int		score;

	va_start(argument, symbol);
	score = 0;
	while (*symbol != '\0')
	{
		if (*symbol == 37)
		{
			symbol++;
			if (*symbol != 37 && *symbol != '\0')
			{
				flags = ft_search_flags(&symbol, &*argument);
				score += ft_argument_all(&symbol, &*argument, flags);
				if (score == -1)
					return (-1);
			}
			else if (*symbol == 37)
				score = score + ft_write_percent(&symbol);
		}
		score = score + ft_write_symbol(&symbol);
	}
	va_end(argument);
	return (score);
}
