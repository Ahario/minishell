SRCS = main.c
LIB = libft
OBJS = ${SRCS:.c=.o}
CC    = gcc
CFLAGS	= -Wextra -Wall -Werror -lreadline -L /usr/local/opt/readline/lib -I \
			/usr/local/opt/readline/include
NAME	= minishell

${LIBFT}: 

${NAME}: ${OBJS}
		@make -C $(LIB)
		cp libft/libft.a $(NAME)
		$(CC) $(CFLAGS) ${SRCS}
		ar -rcs ${NAME} ${OBJS}


all:  ${NAME}

clean:
	 rm -f ${OBJS}
	 @make -C $(LIB) clean
	
fclean :	clean
	rm -f ${NAME}
	@make -C $(LIB) fclean

re : fclean all clean

.PHONY: all bonus clean fclean re
