/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <tbeauman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 08:12:09 by tbeauman          #+#    #+#             */
/*   Updated: 2025/04/13 17:06:00 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../fd_printf/fd_printf.h"
# include "../libft/libft.h"
# include "typedefs.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <signal.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <dirent.h>
# define CHILD 0
#define HISTORY_FILE ".minishell_history"


# define MALLOC_ERROR 1
# define SYNTAX_ERROR 2
# define CMD_NOT_FOUND_ERROR 3

void	get_tokens(t_env *ms);
void	print_error(int err_flag);
void    print_tab(char **tab);
void	handler(int	sig);
void setup_signals(void);
bool	choose_command(t_ast *ast, t_env *ms);
void 	free_tab(char **tab);
bool	execute_cmd(t_tokens *cmd, t_env *ms);
void	cleanup(t_env *ms);
void	exit_clean(t_env *ms, int exit_code);
t_ast   *get_ast(t_tokens **tokens, t_env *ms);
void print_ast(t_ast *node, int depth);
void	ft_tokens_add_back(t_tokens **lst, t_tokens *new);
void	ft_tokens_add_front(t_tokens **lst, t_tokens *new);
void	ft_clear_tokens(t_tokens **lst, void (*del)(void *));
void	ft_del_token(t_tokens *lst, void (*del)(void *));
t_tokens	*ft_new_token(void const *content, t_token_type type);
int	ft_lst_tokens_size(t_tokens *lst);
void	print_tokens(t_tokens *tokens);
void	get_list_tokens(t_env *ms);
int	count_tokens(char *line);
int	string_to_tokens(char *line, int save_count);
bool	has_dquotes(char *tmp);
bool	has_squotes(char *tmp);
int	is_in_set(char c, char const *set);
int	count_chars_to_remove(char const *s1, char const *set);
char	*ft_strtrimv2(char const *s1, char const *set);
void	delete_ast(t_ast **node);
void	search_and_execute_cmd(t_env *ms);
void	consume_tree(t_ast *ast, t_env *ms);
bool	found_builtin(t_tokens *cmd, t_env *ms);
t_tokens	*dup_tokens(t_tokens *og);
void	save_history();
void	handle_append_out(t_ast *ast, t_env *ms);
void	handle_redir_out(t_ast *ast, t_env *ms);
void	handle_redir_in(t_ast *ast, t_env *ms);
void	handle_pipe(t_ast *ast, t_env *ms);
void	consume_tree(t_ast *ast, t_env *ms);
void    expand_tokens(t_ast *ast, t_env *ms);
void    expand_command(t_tokens **cmd, t_env *ms);
void	fork_and_execute_cmd(t_tokens *cmd, t_env *ms);

t_ast	*init_node(void);
t_ast	*handle_parenthesis(t_tokens *tokens, t_tokens **og_tokens, t_env *ms);
void	ft_clear_right_tokens(t_tokens **lst, void (*del)(void *));
void	ft_clear_left_tokens(t_tokens **lst, void (*del)(void *));
void    set_error(t_env *ms, int err_code);

void ft_old_and_pwd(t_env *ms);
void close_all_fds();

void	read_nl_bs(char **next, char **tmp, t_env *ms, int *i);
void	read_nl_quotes(char **next, char **tmp, t_env *ms, int *i);

int	is_operand1(char *str);
int	is_operand2(char *str);
int	is_operand(char *str);
bool	is_dquotes(char *tmp);
bool	is_squotes(char *tmp);

int compute_end_operand_index(char *str, int i, int *start);
int	is_in_set(char c, char const *set);
int	count_chars_to_remove(char const *s1, char const *set);
char	*ft_strtrimv2(char const *s1, char const *set);

bool	add_to_tokens(t_tokens **tokens, char *tmp, char *to_trim, t_token_type type);
bool	token_stops(char *line, int i, bool in_dquotes, bool in_quotes);
void	handle_specials(char *line, int i, t_tknz_bools *t, t_env *ms);
void	check_quotes_ended(t_tknz_bools t, t_env *ms);

t_ast	*init_node(void);
bool	is_not_redir(char *token);
void	cut_chain_and_recursive_call(t_parser *p, t_env *ms);
void	cut_chain_for_redir(t_parser *p, t_env *ms);
void	recursive_call_for_redir(t_parser *p, t_env *ms);

bool	bout_de_scotch(char *cmd_line);

#endif
