#include "ft_printf.h"

static t_list	ft_flags_s(const char *symbol, t_list flags, int *len)
{
	if (flags.point != -1)
	{
		if (flags.point < *len && *symbol != 'c')
			*len = flags.point;
		flags.point = -1;
	}
	if (flags.width <= *len)
		flags.width = 0;
	if (flags.width > *len)
		flags.width = flags.width - *len;
	return (flags);
}

static void	ft_putstr(const char *symbol, char **s, int c, int len)
{
	char	*s2;

	s2 = *s;
	if (*symbol == 'c')
	{
		write(1, &c, 1);
		return ;
	}
	while (len != 0)
	{
		write(1, &*s2, 1);
		s2++;
		len--;
	}
}

static size_t	ft_strlen(const char *symbol, const char *s)
{
	size_t	i;

	if (*symbol == 'c')
		return (1);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

static char	*ft_symbol_s(const char *symbol, va_list arg, t_list flags, char *s)
{
	if (*symbol == 's' && flags.lh != 5)
	{
		s = va_arg(arg, char *);
		if (s == NULL)
			s = "(null)";
	}
	return (s);
}

int	ft_argument_cs(const char *symbol, va_list argument, t_list flags)
{
	int		score;
	char	*s;
	int		c;
	int		len;
	int		w_ch;

	flags.minus = 0;
	c = 0;
	s = 0;
	score = 0;
	if (*symbol == 'c')
		c = va_arg(argument, int);
	s = ft_symbol_s(&*symbol, &*argument, flags, s);
	w_ch = ft_string_w_bonus(&*symbol, &*argument, flags, &s);
	if (w_ch == -1)
		return (-1);
	len = ft_strlen(&*symbol, s);
	flags = ft_flags_s(&*symbol, flags, &len);
	score = flags.width + len;
	flags = ft_filler(&*symbol, flags, len);
	ft_putstr(&*symbol, &s, c, len);
	flags = ft_filler_after(flags);
	return (score);
}
