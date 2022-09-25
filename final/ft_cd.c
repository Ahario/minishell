/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunglee <sunglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 01:50:20 by sunglee           #+#    #+#             */
/*   Updated: 2022/09/25 16:46:39 by lee-sung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_old_pwd(t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i] && ft_strncmp(data->envp[i], "PWD", 3))
		i++;
	return (data->envp[i]);
}

void	put_old_pwd(t_data *data, char *old)
{
	int		i;
	char	*val;

	i = 0;
	while (data->envp[i] && ft_strncmp(data->envp[i], "OLDPWD", 6))
		i++;
	val = find_value(old);
	free(old);
	old = ft_strjoin_normal("OLDPWD=", val);
	free(val);
	free(data->envp[i]);
	data->envp[i] = old;
}

static int	cd_error(char *val)
{
	if (val)
		free(val);
	error_message("cd error\n", NULL);
	return (1);
}

int	ft_get_pwd(t_data *data, char *key, int len, char *val)
{
	char	**envp;
	int		i;

	i = 0;
	envp = data->envp;
	while (envp[i] && ft_strncmp(key, envp[i], (len)))
		i++;
	val = find_value(envp[i]);
	if (envp[i])
	{
		if (chdir(val) == -1)
			return (cd_error(val));
		i = 0;
		while (envp[i] && ft_strncmp(envp[i], "PWD=", 4))
			i++;
		envp[i] = ft_strjoin_normal("PWD=", val);
		free(val);
	}
	else
		return (cd_error(val));
	return (0);
}

static void	ft_cd_pwd(t_data *data)
{
	int		i;
	char	*pwd;

	i = 0;
	while (data->envp[i] && ft_strncmp(data->envp[i], "PWD=", 4))
		i++;
	pwd = getcwd(NULL, 1024);
	data->envp[i] = ft_strjoin_normal("PWD=", pwd);
	free(pwd);
}

void	ft_cd(t_data *data)
{
	t_arg	*arg;
	char	*old;

	old = get_old_pwd(data);
	arg = data->cmd->next;
	if (!arg || !ft_strcmp (arg->ac, "~"))
	{
		if (ft_get_pwd (data, "HOME=", 5, 0))
			return ;
	}
	else if (arg && !ft_strcmp(arg->ac, "-"))
	{
		if (ft_get_pwd (data, "OLDPWD=", 7, 0))
			return ;
	}
	else
	{
		if (chdir(arg->ac) == -1)
		{
			error_message("cd error\n", NULL);
			g_exit_number = 1;
			return ;
		}
		ft_cd_pwd(data);
	}
	put_old_pwd(data, old);
}
