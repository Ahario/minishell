/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 13:15:32 by hyeo              #+#    #+#             */
/*   Updated: 2022/09/25 11:40:39 by lee-sung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

	// t_arg *hed = data->cmd;
	// while(hed != NULL) 
	// {
	// 	printf("%s\n", hed->ac);
	// 	hed = hed->next;
	// }


int add_back_1(t_arg **head, char *ch)
{
	t_arg	*curr;
	t_arg	*new;
	int 		i;

	i = 0;
	curr = *head;
	while (ch[i] != '\0')
	{
		i++;
		if ((ch[i] == ch[0] && ch[i - 1] != '\\'))
		{
			i++;
			break;
		}
	}
	new = malloc(sizeof(t_arg) * 1);
	new->ac = malloc(sizeof(char) * (i + 1));
	ft_strlcpy(new->ac, ch, (i + 1));
	new->next = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		while(curr->next != NULL)
			curr = curr->next;
		curr->next = new;
	}
	return (i);
}

int	check_dq_flag(int flag)
{
	int	i;

	i = flag;
	if (i == 1)
		i = 0;
	else
		i = 1;
	return (i);
}

int	if_char(char const *str)
{
	int	i;
	int	q_flag;
	int	dq_flag;

	q_flag = 0;
	dq_flag = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '\"') || (str[i] == '\''))
		{
			if (str[i] == '\"' && q_flag == 0)
				dq_flag = check_dq_flag(dq_flag);
			else if (str[i] == '\'' && dq_flag == 0)
				q_flag = check_dq_flag(q_flag);
		}
		if (q_flag == 0 && dq_flag == 0 && str[i] == ' ')
			break ;
		i++;
	}
	return (i);
}

// int add_back_1(t_arg **head, char *ch)
// {
// 	t_arg	*curr;
// 	t_arg	*new;
// 	int 		i;

// 	i = 0;
// 	curr = *head;
// 	while (ch[i] != '\0')
// 	{
// 		i++;
// 		if ((ch[i] == ch[0] && ch[i - 1] != '\\'))
// 		{
// 			i++;
// 			break;
// 		}
// 	}
// 	new = malloc(sizeof(t_arg) * 1);
// 	new->ac = malloc(sizeof(char) * (i + 1));
// 	ft_strlcpy(new->ac, ch, (i + 1));
// 	new->next = NULL;
// 	if (*head == NULL)
// 		*head = new;
// 	else
// 	{
// 		while(curr->next != NULL)
// 			curr = curr->next;
// 		curr->next = new;
// 	}
// 	return (i);
// }

void	add_back(t_arg **head, char *ch)
{
	t_arg	*curr;
	t_arg	*new;

	curr = *head;
	new = malloc(sizeof(t_arg) * 1);
	new->ac = malloc(sizeof(char) * (if_char(ch) + 1));
	ft_strlcpy(new->ac, ch, (if_char(ch) + 1));
	new->next = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = new;
	}
}

void play_built(t_data *data, char *str)
{
	if (ft_strncmp(str, "echo", ft_strlen(str)) == 0)
		ft_echo(data, 0);
	else if (ft_strncmp(str, "cd", ft_strlen(str)) == 0)
		ft_cd(data);
	else if (ft_strncmp(str, "pwd", ft_strlen(str)) == 0)
		ft_pwd(data);
	else if (ft_strncmp(str, "export", ft_strlen(str)) == 0)
		ft_export(data);
	else if (ft_strncmp(str, "unset", ft_strlen(str)) == 0)
		ft_unset(data);
	else if (ft_strncmp(str, "env", ft_strlen(str)) == 0)
		ft_env(data->envp);
	else if (ft_strncmp(str, "exit", ft_strlen(str)) == 0)
		ft_exit(data);
	return ;
}


int	check_built(t_data *data, char *str)
{
	(void)data;
	if (ft_strncmp(str, "echo", ft_strlen(str)) == 0)
		return (0);
	else if (ft_strncmp(str, "cd", ft_strlen(str)) == 0)
		return (0);
	else if (ft_strncmp(str, "pwd", ft_strlen(str)) == 0)
		return (0);
	else if (ft_strncmp(str, "unset", ft_strlen(str)) == 0)
		return (0);
	else if (ft_strncmp(str, "env", ft_strlen(str)) == 0)
		return (0);
	else if (ft_strncmp(str, "exit", ft_strlen(str)) == 0)
		return (0);
	else if (ft_strncmp(str, "export", ft_strlen(str)) == 0)
		return (0);
	return (1);
}

int	check_q(char *str)
{
	int	i;
	int	dq_flag;

	i = 0;
	dq_flag = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
		{
			if (dq_flag == 1)
				dq_flag = 0;
			else
				dq_flag = 1;
		}
		if (str[i] == '\'' && dq_flag == 0)
			return (0);
		i++;
	}
	return (1);
}

int	check_dq(char *str)
{
	int	i;
	int	q_flag;

	i = 0;
	q_flag = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
		{
			if (q_flag == 1)
				q_flag = 0;
			else
				q_flag = 1;
		}
		if (str[i] == '\"' && q_flag == 0)
			return (0);
		i++;
	}
	return (1);
}

int	check_redirect(char *str)
{
	if (str[0] == '<' && str[1] == '<')
		return (0);
	else if (str[0] == '>' && str[1] == '>')
		return (0);
	else if (str[0] == '>')
		return (0);
	else if (str[0] == '<')
		return (0);
	return (1);
}

int	check_exitnumber(char *str)
{
	if (str[0] == '$' && str[1] == '?')
		return (0);
	return (1);
}

int	check_pipe(char *str)
{
	if (str[0] == '|')
		return (0);
	return (1);
}

void	assign_q(t_arg **head)
{
	t_arg	*curr;

	curr = *head;
	curr->type = SINQ;
}

void	assign_dq(t_arg **head)
{
	t_arg	*curr;

	curr = *head;
	curr->type = DOUQ;
}

void	assign_redirect(t_arg **head)
{
	t_arg	*curr;

	curr = *head;
	curr->type = RDRT;
}

void	assign_pipe(t_arg **head)
{
	t_arg	*curr;

	curr = *head;
	curr->type = PIPE;
}

void	assign_norm(t_arg **head)
{
	t_arg	*curr;

	curr = *head;
	curr->type = NORM;
}

void	assign_parse(t_data *data)
{
	t_arg	*curr;

	curr = data->cmd;
	while (curr != NULL)
	{
		if (check_q(curr->ac) == 0)
			assign_q(&curr);
		else if (check_dq(curr->ac) == 0)
			assign_dq(&curr);
		else if (check_redirect(curr->ac) == 0)
			assign_redirect(&curr);
		else if (check_pipe(curr->ac) == 0)
			assign_pipe(&curr);
		else
			assign_norm(&curr);
		curr = curr->next;
	}
	parse_bigpart(data);
}

void	parse_bigpart(t_data *data)
{
	int		flag;
	t_arg	*curr;

	flag = 0;
	curr = data->cmd;

	while (curr != NULL)
	{
		flag = 0;
		curr->ac = replace_ds_parse(curr->ac, data, flag);
		curr = curr->next;
	}
	replace_parse(data);
}


int	total_path_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != ' ' && str[i] != '\0'
		&& str[i] != '\"' && str[i] != '\'' && str[i] != '$')
	i++;
	return (i);
}

char	*get_path(char *str)
{
	int		i;
	int		j;
	char	*temp;

	temp = NULL;
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			i++;
			temp = malloc(sizeof(char) * (total_path_len(&str[i]) + 1));
			while (j != total_path_len(&str[i]))
			{
				temp[j] = str[i + j];
				j++;
			}
			temp[j] = '\0';
			break ;
		}
		i++;
	}
	return (temp);
}

int	search_mini_path(int j, char *envp[], char *str)
{
	int	i;

	i = 0;
	while (envp[j][i] == str[i])
	{
		if (str[i] == envp[j][i])
			i++;
		else
			return (1);
	}
	if (envp[j][i] == '=' && str[i] == '\0')
		return (0);
	return (1);
}

char	*get_full_path(char *str, t_data *data)
{
	int		i;
	int		j;
	int		k;
	char	*temp;

	i = 0;
	j = 0;
	k = 0;
	temp = NULL;
	while (data->envp[i] != NULL && search_mini_path(i, data->envp, str))
		i++;
	if (data->envp[i] == NULL)
		return (temp);
	while (data->envp[i][j] != '=')
		j++;
	j++;
	temp = malloc(sizeof(char) * (ft_charlen(&data->envp[i][j]) + 1));
	while (data->envp[i][j] != '\0')
		temp[k++] = data->envp[i][j++];
	temp[k] = '\0';
	return (temp);
}

char	*replace_dollar_sign(char *st, t_data *data)
{
	char	*temp;
	char	*temp2;
	int		i;

	temp = NULL;
	temp2 = NULL;
	i = 0;
	while (st[i] != '\0')
	{
		if (st[i] == '$')
		{
			if (st[i] == '$' && st[i + 1] == '?')
			{
				temp2 = ft_itoa(g_exit_number);
				temp = get_full_exit(temp2, &st[i + 2]);
				free(temp2);
			}
			else if ((st[i] == '$' && st[i + 1] == '\0') || (st[i] == '$' && st[i + 1] == '\"')
						|| (st[i] == '$' && st[i + 1] == '\'') || (st[i] == '$' && st[i + 1] == ' '))
			{
				temp = malloc(sizeof(char) * (2));
				temp[0] = '$';
				temp[1] = '\0';
			}
			else
			{
				temp2 = get_path(st);
				temp = get_full_path(temp2, data);
				free(temp2);
			}
			return (temp);
		}
		i++;
	}
	return (NULL);
}

int	for_before_r_ds_parse(char *c)
{
	int	i;

	i = 0;
	if (c[i] != '\"' && c[i] != '\'' && c[i] != '\0'
		&& c[i] != ' ' && c[i] != '$')
		return (0);
	return (1);
}

void	increase_both(int *i, int *j)
{
	*i += 1;
	*j += 1;
}

int	before_r_ds_parse(char *str, t_data *data)
{
	int		i;
	int		j;
	int		flag;
	char	*temp;

	i = 0;
	j = 1;
	flag = 0;
	temp = NULL;
	while (str[i] != '\0')
	{
		flag = check_flag(flag, &str[i]);
		if (str[i] == '$' && flag != 2)
		{
			temp = replace_dollar_sign(&str[i], data);
			j += ft_charlen_export(temp);
			free(temp);
			temp = NULL;
			i++;
			while (for_before_r_ds_parse(&str[i]) == 0)
				i++;
		}
		else
			increase_both(&i, &j);
	}
	return (j);
}

int	for_replace_ds_parse(char *c)
{
	int	i;

	i = 0;
	if (c[i] != '\"' && c[i] != '\'' && c[i] != '\0'
		&& c[i] != ' ' && c[i] != '$')
		return (0);
	return (1);
}

void	reset_replace_ds_parse(int *flag, int *i, int *k)
{
	*flag = 0;
	*i = 0;
	*k = 0;
}

void	if_replace_ds_parse(int *k, char *c, char *t, t_data *data)
{
	int		i;
	int		j;
	char	*temp2;

	i = 0;
	j = 0;
	temp2 = replace_dollar_sign(&c[i], data);
	if (!temp2)
		return ;
	while (temp2[i] != '\0')
		t[j++] = temp2[i++];
	free(temp2);
	*k += j;
}

void	if_replace_ds_parse_dq(int *k, char *c, char *t, t_data *data)
{
	int		i;
	int		j;
	char	*temp2;

	i = 0;
	j = 0;
	temp2 = replace_dollar_sign_dq(&c[i], data);
	if (!temp2)
		return ;
	while (temp2[i] != '\0')
	{
		if (j == 0 && temp2[i] != '\0' && temp2[i] != ' ')
			t[j++] = '\"';
		if (temp2[i] == ' ')
		{
			while (temp2[i] != '\0' && temp2[i] == ' ')
					i++;
			if (j == 0 && temp2[i] != '\0' && temp2[i] != ' ')
				t[j++] = '\"';
			if (temp2[i] != '\0' && j != 0)
				t[j++] = ' ';
		}
		else
			t[j++] = temp2[i++];
	}
	t[j++] = '\"';
	*k += j;
	free(temp2);
}

char	*get_full_exit(char *temp, char *str)
{
	int		i;
	int		j;
	char *temp2;

	i = 0;
	j = 0;
	temp2 = malloc(sizeof(char) * (ft_charlen(temp) + (ft_charlen(str)) + 1));
	while (temp[i] != '\0')
		temp2[j++] = temp[i++];
	i = 0;
	while (str[i] != '\0')
		temp2[j++] = str[i++];
	temp2[j] = '\0';
	return (temp2);
}


char	*replace_dollar_sign_dq(char *st, t_data *data)
{
	char	*temp;
	char	*temp2;
	int		i;

	temp = NULL;
	temp2 = NULL;
	i = 0;
	while (st[i] != '\0')
	{
		if (st[i] == '$')
		{
			if (st[i] == '$' && st[i + 1] == '?')
			{
				temp2 = ft_itoa(g_exit_number);
				temp = get_full_exit(temp2, &st[i + 2]);
				free(temp2);
			}
			else if (st[i] == '$' && st[i + 1] == '\0')
			{
				temp = malloc(sizeof(char) * (2));
				temp[0] = '$';
				temp[1] = '\0';
			}
			else
			{
				temp2 = get_path(st);
				temp = get_full_path_dq(temp2, data);
				free(temp2);
			}
			return (temp);
		}
		i++;
	}
	return (NULL);
}

char	*get_full_path_dq(char *str, t_data *data)
{
	int		i;
	int		j;
	int		k;
	char	*temp;

	i = 0;
	j = 0;
	k = 0;
	temp = NULL;
	while (data->envp[i] != NULL && search_mini_path(i, data->envp, str))
		i++;
	if (data->envp[i] == NULL)
	{
		return (temp);
	}
	while (data->envp[i][j] != '=')
		j++;
	j++;
	while (data->envp[i][j] != '\0' && data->envp[i][j] == ' ')
		j++;
	temp = malloc(sizeof(char) * (ft_charlen(&data->envp[i][j]) + 1));
	while (data->envp[i][j] != '\0')
		temp[k++] = data->envp[i][j++];
	temp[k] = '\0';
	return (temp);
}

void	add_i(int *i, char *str)
{
	int k;

	k = 0;
	k++;
	while (for_replace_ds_parse(&str[k]) == 0)
		k++;
	*i += k;
}

char	*replace_ds_parse(char *str, t_data *data, int flag)
{
	char	*temp;
	int		i;
	int		k;

	i = 0;
	k = 0;
	temp = malloc(sizeof(char) * ((before_r_ds_parse(str, data)) + 1));
	while (str[i] != '\0')
	{
		flag = check_flag(flag, &str[i]);
		if (str[i] == '$' && flag != 2)
		{
			if (flag == 1)
				if_replace_ds_parse(&k, &str[i], &temp[k], data); //$a : copy like my parsing
			else
				if_replace_ds_parse_dq(&k, &str[i], &temp[k], data); //"$a" : copy everything
			add_i(&i, &str[i]);
		}
		else
			temp[k++] = str[i++];
	}
	temp[k] = '\0';
	free(str);
	return (temp);
}

char	*ft_strcpy_hth(char *str, int here, int there)
{
	int		i;
	int		j;
	char	*temp;

	i = here;
	j = 0;
	temp = NULL;
	temp = malloc(sizeof(char) * (there - here));
	while (i + j != there)
	{
		temp[j] = str[i + j];
		j++;
	}
	temp[j] = '\0';
	return (temp);
}

int	get_temp_size(char *str)
{
	int		i;
	int		j;
	char	charset;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '\"' || str[i] == '\''))
		{
			charset = str[i];
			i++;
			while (str[i] != charset && str[i] != '\0')
			{
				i++;
				j++;
			}
		}
		else
		{
			i++;
			j++;
		}
	}
	return (j);
}

void	if_replace_parse(char *str, char *temp, int *i, int *j)
{
	int		k;
	int		l;
	char	charset;

	k = 0;
	l = 0;
	charset = str[k];
	k++;
	while (str[k] != charset && str[k] != '\0')
		temp[l++] = str[k++];
	if (str[k] != '\0')
		k++;
	*i += k;
	*j += l;
}

char	*reset_replace_parse(int *i, int *j, char *str)
{
	char	*temp;

	temp = malloc(sizeof(char) * (get_temp_size(str) + 1));
	*i = 0;
	*j = 0;
	return (temp);
}

void	replace_parse(t_data *data)
{
	int		i;
	int		j;
	char	*temp;
	t_arg	*curr;

	i = 0;
	j = 0;
	temp = NULL;
	curr = data->cmd;
	while (curr != NULL)
	{
		temp = (reset_replace_parse(&i, &j, curr->ac));
		while (curr->ac[i] != '\0')
		{
			if (curr->ac[i] == '\'' || curr->ac[i] == '\"')
				if_replace_parse(&curr->ac[i], &temp[j], &i, &j);
			else
				temp[j++] = curr->ac[i++];
		}
		temp[j] = '\0';
		free(curr->ac);
		curr->ac = temp;
		temp = NULL;
		curr = curr->next;
	}
	t_arg *hed = data->cmd;
	while(hed != NULL) 
	{
		printf("this is it : %s\n", hed->ac);
		hed = hed->next;
	}
}

int	check_flag(int flag, char *str)
{
	int	i;

	i = flag;
	if (str[0] == '\"' && i != 2)
	{
		if (i == 1)
			i = 0;
		else
			i = 1;
	}
	if (str[0] == '\'' && i != 1)
	{
		if (i == 2)
			i = 0;
		else
			i = 2;
	}
	return (i);
}

int	ft_charlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	for_ft_find_red(char *c, int f)
{
	int	i;

	i = f - 1;
	if (f > 0)
	{
		if ((c[i] == '<' && c[f] == '<') || (c[f] == '>' && c[f] == '>'))
			return (0);
	}
	return (1);
}

int	ft_find_red(char *str)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	flag = 0;
	while (str[i] != '\0')
	{
		flag = check_flag(flag, &str[i]);
		if ((str[i] == '|' || str[i] == '<' || str[i] == '>' ) && flag == 0)
		{
			if (for_ft_find_red(str, i) == 0)
				i++;
			else
				j++;
		}
		i++;
	}
	return (j);
}

int	check_dq_pair(char *str)
{
	int	i;
	int	q_flag;
	int	dq_flag;

	q_flag = 0;
	dq_flag = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '\"') || (str[i] == '\''))
		{
			if (str[i] == '\"' && q_flag == 0)
				dq_flag = check_dq_flag(dq_flag);
			else if (str[i] == '\'' && dq_flag == 0)
				q_flag = check_dq_flag(q_flag);
		}
		i++;
	}
	if (q_flag == 1 || dq_flag == 1)
		return (0);
	return (1);
}


int		check_parse(char *ch, t_data *data)
 {
 	int	i;
 	int	flag;

 	i = 0;
 	flag = 0;
	(void)data;
 	while (ch[i] != '\0')
 	{
 		if (ch[i] != ' ')
 		{
 			flag = 1;
 			break;
 		}
 		i++;
 	}
	flag = check_dq_pair(ch);
 	return (flag);
 }

void	increase_temp(char *temp, char *ch, int *k, int *l)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	temp[j++] = ch[++i];
	temp[j++] = ch[i++];
	*l += 2;
	*k += 2;
}

int	for_red(char *c, int f)
{
	int	i;

	i = 0;
	if ((c[i] == '|' || c[i] == '<' || c[i] == '>') && f == 0)
		return (0);
	return (1);
}

int	for_d_red(char *c)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	if (c[j] != '\0' && ((c[i] == '<' && c[j] == '<')
			|| (c[i] == '>' && c[j] == '>') || (c[i] == '|' && c[j] == '|')))
		return (0);
	return (1);
}

int	ft_charlen_export(char *str)
{
	int	i;
	int	j;

	j = 2;
	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		i++;
		j++;
	}
	return (j);
} 

void	before_parse(char *ch, t_data *data)
{
	int		i;
	int		j;
	int		flag;
	char	*temp;

	i = 0;
	j = 0;
	flag = 0;
	temp = malloc(sizeof(char) * (ft_charlen(ch) + ft_find_red(ch)) + 4);
	while (ch[i] != '\0')
	{
		flag = check_flag(flag, &ch[i]);
		if (for_red(&ch[i], flag) == 0)
		{
			if (ch[i - 1] != ' ')
				temp[j++] = ' ';
			if (for_d_red(&ch[i]) == 0)
				increase_temp(&temp[j], &ch[i], &i, &j);
		}
		temp[j++] = ch[i++];
		if (i > 0 && ((ch[i - 1] == '|' && ch[i] != ' ' && ch[i] != '|')))
			temp[j++] = ' ';
		// if (i > 1 && ((ch[i - 1] == '\"' && ch[i - 2] == '$')))
		// 	temp[j++] = ' ';
	}
	temp[j] = '\0';
	printf("%s\n", temp);
	parse(temp, data);
}

void	parse(char *ch, t_data *data)
{
	int		i;
	t_arg	*head;

	i = 0;
	head = NULL;
	data->argc = ft_strlen(ch);
	while (ch[i] != '\0')
	{
		if ((ch[i] != '\'' && ch[i] != '\"')
			|| (ch[i] == '\"' || ch[i] == '\''))
		{
			while (ch[i] == ' ')
				i++;
			if (ch[i] != '\0')
			{
				add_back(&head, &ch[i]);
				i += (if_char(&ch[i]));
			}
		}
		else if (ch[i] == '\"' || ch[i] == '\'')
			i += (add_back_1(&head, &ch[i]));
	}
	data->cmd = head;
	free(ch);
	assign_parse (data);
}

void	ft_set_data(t_data *data)
{
	data->fd_in = -1;
	data->fd_out = -1;
	data->prev = NULL;
	data->next = NULL;
}


struct s_data	*clean_all(t_data *data)
{
	t_arg	*next;
	t_data	*d_next;
	char	**new_envp;
	t_data	*new;

	if (!data->cmd)
		return (data);
	new_envp = ft_malloc_envp(data->envp);
	while (data)
	{
		while (data->cmd)
		{
			if (data->cmd->ac)
				free(data->cmd->ac);
			next = data->cmd->next;
			if (data->cmd)
				free(data->cmd);
			data->cmd = next;
		}
		d_next = data->next;
		if (!data->prev)
			free_split(data->envp);
		if (data->pipe && data->next)
			free(data->pipe);
		free(data);
		data = d_next;
	}
	new = (t_data *)malloc(sizeof(t_data));
	new->envp = new_envp;
	ft_set_data(new);
	return (new);
}


char	**ft_malloc_envp(char **envp)
{
	int		i;
	char	**ret;

	i = 0;
	while(envp[i])
		i++;
	ret = (char **)malloc(sizeof(char *) * (i + 1));
	if (!ret)
		return (NULL);
	ret[i] = NULL;
	i -= 1;
	while(i >= 0 && envp[i])
	{
		ret[i] = ft_strdup(envp[i]);
		i--;
	}
	return (ret);
}

struct s_data	*ft_before(int argc, char *argv[], char **envp)
{
	t_data			*data;
	struct termios	change;

	(void)argc;
	(void)argv;
	tcgetattr(STDIN_FILENO, &change);
	change.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &change);
	g_exit_number = 0;
	data = (t_data *)malloc(sizeof(t_data));
	ft_set_data(data);
	data->envp = ft_malloc_envp(envp);
	ft_signal();
	return (data);
}

int	main(int argc, char *argv[], char **envp)
{
	t_data			*data;
	struct termios	terminal;
	char			*ch;

	tcgetattr(STDIN_FILENO, &terminal);
	data = ft_before(argc, argv, envp);
	while (1)
	{
		ch = readline("MINISHELL./ ");
		if (ch)
		{
			if (check_parse(ch, data))
			{
				before_parse(ch, data);
				if(!ft_redir(data))
					ft_cmd_start(data);
			}
		}
		else if (!ch)
			exit_c_d();
		add_history(ch);
		data = clean_all(data);
		free(ch);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &terminal);
	return (0);
}
