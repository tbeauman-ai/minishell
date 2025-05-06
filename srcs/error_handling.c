/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:05:36 by tbeauman          #+#    #+#             */
/*   Updated: 2025/05/05 12:51:30 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	set_error(t_env *ms, int err_code)
{
	ms->last_exit_code = err_code;
	return (true);
}
bool	set_parse_error(t_env *ms, int err_code)
{
	ms->parse_error = err_code;
	return (true);
}