NAME		=	libftprintf.a

CC			=	gcc
RM			=	rm -f 

CFLAGS		=	-Wall -Wextra -Werror

SRCS		=	ft_printf.c ft_search_flags.c \
				ft_argument_di.c ft_argument_cs.c \
				ft_argument_xxp.c ft_argument_u.c\
				ft_filler.c ft_filler_after.c \
				ft_point_width_dx.c \
				ft_no_argument.c \
				ft_flags_bonus.c ft_string_w_bonus.c \
				ft_search_width.c ft_flags_lh_bonus.c \

BONUS_FILES	=	ft_flags_bonus.c ft_flags_lh_bonus.c ft_string_w_bonus.c\

OBJS_BONUS	=	${BONUS_FILES:.c=.o}


OBJS		=	${SRCS:.c=.o}

HEADER		=  -I ft_printf.h

.c.o:		=	ft_printf.h
			${CC} ${CFLAGS} -c $< ${HEADER} -o ${<:.c=.o} 

${NAME}:	${OBJS}
			ar rcs ${NAME} ${OBJS}

all:		${NAME}
	
clean:	
			${RM} ${OBJS} ${OBJS_BONUS}
			
fclean:		clean
			${RM} ${NAME} 

re:			fclean all 

rebonus: 	fclean bonus

bonus:		all ${OBJS_BONUS}
			ar rcs ${NAME} ${OBJS_BONUS} 

.PHONY: all clean fclean re bonus