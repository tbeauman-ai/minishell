/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:46:56 by elopin            #+#    #+#             */
/*   Updated: 2025/05/06 17:52:36 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

void	ft_trie_env(t_env *ms)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	if (!ms->envp && set_error(ms, 1))
		return ;
	while (ms->envp[i] && ms->envp[i + 1])
	{
		if (ft_strcmp(ms->envp[i], ms->envp[i + 1]) > 0)
		{
			tmp = ms->envp[i];
			ms->envp[i] = ms->envp[i + 1];
			ms->envp[i + 1] = tmp;
			i = -1;
		}
		i++;
	}
}

void	print_export(t_env *ms)
{
	t_env	*tmp;
	int		i;
	char	*str;

	tmp = NULL;
	i = 0;
	str = NULL;
	if (!ms)
		return ;
	tmp = ms;
	if (!tmp->envp && set_error(ms, 1))
		return ;
	ft_trie_env(ms);
	while (tmp->envp[i] != NULL)
	{
		if (ft_strchr(tmp->envp[i], '='))
			str = add_guillemet(tmp->envp[i]);
		else
			str = ft_strdup(tmp->envp[i]);
		if (!str && set_error(ms, 1))
			return ;
		printf("declare -x %s\n", str);
		free(str);
		i++;
	}
}

int	ft_export(t_env *ms, char *var)
{
	char	*key;
	int		h;
	int		i;

	i = -1;
	h = 0;
	if (!var || var[0] == '=')
		return (set_error(ms, 1), 1);
	if (ft_strchr(var, '&'))
		return (printf("export: `%s': not a valid identifier\n", var),
			set_error(ms, 1));
	key = ft_substr(var, 0, find_index(var, '='));
	if (!key && set_error(ms, 1))
		return (1);
	if (!ft_isalpha(key[0]))
		return (set_error(ms, 1), free(key), 1);
	h = find_key(ms->envp, key);
	free(key);
	if (h >= 0)
		update_export(ms, var, h);
	else
		creat_export(ms, var);
	return (ms->last_exit_code = 0, 1);
}

int	ft_shlvl(t_env *ms)
{
	int		b;
	int		i;
	char	*tmp;
	char	*str;

	b = 0;
	tmp = NULL;
	str = NULL;
	i = find_key(ms->envp, "SHLVL");
	if (i < 0 && ft_export(ms, "SHLVL=1"))
		return (set_error(ms, 1), 1);
	str = ft_substr(ms->envp[i], find_index(ms->envp[i], '=') + 1,
			ft_strlen(ms->envp[i]));
	if (!str && set_error(ms, 1))
		return (set_error(ms, 1), 1);
	b = ft_atoi(str) + 1;
	free(str);
	tmp = ft_itoa(b);
	if (!tmp)
		return (set_error(ms, 1), 0);
	str = ft_strjoin("SHLVL=", tmp);
	free(tmp);
	if (!str)
		return (0);
	return (ft_export(ms, str), free(str), 1);
}

void	ft_old_and_pwd(t_env *ms)
{
	char	*str;
	char	*tmp;

	str = print_path(0);
	tmp = NULL;
	tmp = ft_strjoin("PWD=", str);
	if (find_key(ms->envp, "OLDPWD") < 0)
		ft_export(ms, "OLDPWD");
	ft_export(ms, tmp);
	free(tmp);
	free(str);
	ft_shlvl(ms);
}
