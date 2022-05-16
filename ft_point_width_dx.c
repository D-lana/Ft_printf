#include "ft_printf.h"

t_list	ft_flags_for_di(t_list flags, int *score)
{
	if (flags.width == 0 && flags.b == 2 && flags.minus == 0)
		*score = *score + 1;
	if (flags.b == 2 && flags.width != 0 && flags.minus == 0)
		flags.width--;
	if (flags.width == 0 && flags.b == 3 && flags.minus == 0)
		*score = *score + 1;
	if (flags.width != 0 && flags.b == 3 && flags.minus == 0)
		flags.width--;
	return (flags);
}

t_list	ft_octothorpe_xxp(t_list flags, int *score)
{
	if (flags.width == 1 && flags.b == 1)
		*score = *score + 1;
	if (flags.width == 0 && flags.b == 1)
		*score = *score + 2;
	if (flags.b == 1 && flags.width == 1)
		flags.width = flags.width - 1;
	if (flags.b == 1 && flags.width >= 2)
		flags.width = flags.width - 2;
	return (flags);
}

t_list	ft_point_p(t_list flags, int *score, const char **s, int *len)
{
	const char	*symbol_2;

	symbol_2 = *s;
	if (flags.point >= 0 && *symbol_2 == 'p')
	{
		if (flags.point <= *len - 2)
			flags.point = *len;
		else if (flags.point > *len - 2)
			flags.point += 2;
		if (flags.width <= flags.point - 2)
			flags.width = 0;
		if (flags.width > flags.point - 2 && flags.width - flags.point >= 0)
			flags.width = flags.width - flags.point;
		if (flags.width == flags.point - 1)
			flags.width = flags.width - flags.point + 1;
		*score = flags.point + flags.width;
	}
	return (flags);
}

t_list	ft_point_width_dx(t_list flags, int *score, int *len, const char *s)
{
	*score = 0;
	if (flags.point >= 0 && *s != 'p')
	{
		if ((flags.point <= *len && *s != 'p'))
			flags.point = *len;
		if (flags.width <= flags.point)
			flags.width = 0;
		if (flags.width > flags.point)
			flags.width = flags.width - flags.point - flags.minus;
		*score = flags.point + flags.width + flags.minus;
	}
	else if (flags.point < 0)
	{
		if (flags.width <= *len + flags.minus)
			flags.width = 0;
		else
			flags.width = flags.width - *len - flags.minus;
		*score = flags.width + *len + flags.minus;
	}
	flags = ft_point_p(flags, &*score, &s, &*len);
	if (*s == 'd' || *s == 'i')
		flags = ft_flags_for_di(flags, &*score);
	if (*s == 'x' || *s == 'X')
		flags = ft_octothorpe_xxp(flags, &*score);
	return (flags);
}
