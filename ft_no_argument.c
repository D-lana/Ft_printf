#include "ft_printf.h"

int	ft_no_argument(const char *symbol, t_list flags)
{
	int	score;
	int	len;

	len = 0;
	flags.minus = 0;
	score = flags.width;
	flags.width = flags.width - 1;
	flags.point = -1;
	flags = ft_filler(&*symbol, flags, len);
	write(1, "%%", 1);
	flags = ft_filler_after(flags);
	return (score);
}
