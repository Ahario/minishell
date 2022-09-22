/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 13:15:40 by hyeo              #+#    #+#             */
/*   Updated: 2022/09/22 13:15:44 by hyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>
#include <sys/signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

int	g_exit_number;

typedef struct s_arg{
	char	*ac;
	int		type;
	int		fd_in;
	int		fd_out;
	struct s_arg	*next;
}	t_arg;

typedef struct s_data{
	t_arg			*cmd;
	int				argc;
	char			**argv;
	char			**envp;
	struct s_data	*next;
	struct s_data	*prev;
}	t_data;


enum	e_pars{
    NORM, SPCE, SINQ, DOUQ, BSLA, DOLR,
    PIPE, DPIP, SEMC, DSEM,
    RDRT, DRGT
};

//t_arg	*set_cmd(char *ch);
void	before_init(void);
void	ft_signal(void);
void	ft_exit(void);

void replace_ds_parse(t_data *data);
char *replace_dollar_sign(char *str, t_data *data);
void replace_parse(t_data *data);
int get_temp_size(char *str);
void parse(char *ch, t_data *data);
int check_flag(int flag, char *str);
int totla_path_len(char *str);
int ft_charlen(char *str);

#endif
