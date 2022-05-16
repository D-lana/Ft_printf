#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <limits.h>
# include <wchar.h>
# include <stdlib.h>

typedef struct s_list
{
	int				width;
	int				fill_in;
	int				point;
	int				minus;
	int				zero;
	int				b;
	int				lh;

	struct s_list	*next;
}					t_list;

int		ft_printf(const char *symbol, ...);
int		ft_argument_cs(const char *symbol, va_list argument, t_list flags);
int		ft_argument_di(const char *symbol, va_list argument, t_list flags);
int		ft_argument_u(const char *symbol, va_list argument, t_list flags);
int		ft_argument_xxp(const char *symbol, va_list argument, t_list flags);
int		ft_no_argument(const char *symbol, t_list flags);
int		ft_search_width(va_list argument, const char **symbol_2);
int		ft_string_w_bonus(const char *s, va_list arg, t_list flags, char **s1);

t_list	ft_search_flags(const char **symbol, va_list argument);
t_list	ft_filler(const char *symbol, t_list flags, int len);
t_list	ft_filler_after(t_list flags);
t_list	ft_point_width_dx(t_list flags, int *score, int *len, const char *s);

t_list	ft_flags_bonus(const char **symbol_2, t_list flags);
t_list	ft_flags_lh_bonus(const char **symbol_2, t_list flags);

#endif