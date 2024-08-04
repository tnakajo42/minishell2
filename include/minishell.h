/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:06:07 by cadenegr          #+#    #+#             */
/*   Updated: 2024/08/02 12:04:05 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <sys/ioctl.h>

# define MAX_PATH_SIZE		8192
# define MAX_HISTORY		8192
# define MAX_ENV_NAME		8192
# define MAX_ENV_VALUE		8192

struct	s_main;

typedef struct s_input
{
	int					input_len;
	int					is_alnum;
	int					nested_single;
	int					nested_double;
	int					single_q;
	int					double_q;
	int					quoted_words;
	int					right_d;
	int					left_d;
	int					slash;
	int					semicolon;
	int					dollar;
	int					question;
	int					andsign;
	int					is_pipe;
	int					is_whitespc;
	int					from_double;
	int					exit_status;
	int					back_slash_flag;
	bool				out_double;
	char				*code_line;
	char				**split;
	struct s_main		*m;
}	t_in;

typedef struct s_token
{
	char	*string;
	char	*type;
}	t_token;

typedef struct s_llist
{
	void			*data;
	struct s_llist	*prev;
	struct s_llist	*next;
}	t_llist;

typedef struct s_history
{
	int					last_exit_status;
	char				*commands[MAX_HISTORY];
	int					count;
	int					current_history_index;
}	t_history;

typedef struct s_main
{
	char		**cmds;
	char		**checkout;
	char		**env;
	char		**files;
	int			dollar_str;
	int			i;
	int			break_flag;
	bool		ctrld_firstrun;
	bool		what_is;
	bool		is_echo;
	int			home_position;
	char		*pwd;
	t_in		in;
	t_p			*p;
	t_list		*lst;
	t_list		*lenv;
	t_history	history;
}	t_m;

typedef struct s_len
{
	size_t		name_len;
	size_t		value_len;
}	t_len;

//init_struct.c
int			init_file_names(t_m *m);
int			init_struct_input_2(t_m *m);
int			init_struct_input(t_m *m);
void		init_t_history(t_m *m);
void		init_before_display(t_m *m);
//files.c
int			path_env(char **env, t_m *m);
int			path_input(t_m *m);
int			path_visualizer(t_m *m);
int			path_checkout(t_m *m);
int			path_outcome_results(t_m *m);
//save_input.c
void		copy_file(char *src, char *dest);
void		copy_file_append(char *src, char *dest);
void		remove_files(char **rm_files);
void		save_in_file_trunc(char *data, char *file_name);
void		save_in_file_append(char *data, char *file_name);
//test_print_function.c
char		*get_input(char *input);
int			error(char *s);
void		print_in_dec(char *str);
int			p(void *arg, int type);
//display.c
void		minishell_free(t_m *m);
int			update_input(char *input, t_m *m);
int			store_env(t_m *m);
int			display_processes(char *input, t_m *m);
void		simple_prompt_display(t_m *m);
// execute.c
void		try_execute(t_m *m, char *input, char **env);
int			builtin_execute(t_m *m, char *str, int fd);
void		remove_newline(char *str);
//simu.c
int			simu_exec_wout_execute(char *cmd, char **env, t_m *m, t_p *p);
int			simu_which_path(char *cmd, char **env, t_p *p, t_m *m);
int			simu_ft_access(char *cmd, t_p *p, t_m *m);
// builtins folder
char		*ft_getenv(t_m *m, char *name);
int			show_dollar_data(char *content, t_m *m, int type);
int			get_dollar_data_len(char *str, int i);
int			get_doll_visual(char *str, int i, t_m *m);
int			get_dollar_data(char *dest, char *str, int i);
int			cd_cmd(char *str, t_m *m);
int			echo_cmd(char *str, t_m *m, int i);
int			pwd_cmd(char *str, t_m *m);
int			env_cmd(char *str, t_m *m);
int			echo_cmd_print(char *str, t_m *m, int i);
int			exit_cmd(char *str, t_m *m);
int			export_cmd(char *str, t_m *m);
int			unset_cmd(char *str, t_m *m);
int			ft_isspace(char *s);
char		*ft_strncpy_for_export_name(char *dest, char *src, unsigned int n);
//visualizer.c
int			write_str_num(char *s, int n, int fd);
int			pipe_or_redirect(char *s);
int			cont_file_analize(char *line, t_m *m, int fd);
void		file_analize_loop(int fd, t_m *m);
int			file_analize(char *line, t_m *m);
//ft_checkout.c
int			save_checkout_send_super(char *types, char **env, t_m *m);
int			checkout_maker(int read, char *input, char **env, t_m *m);
char		*checkout_cmds_shorter(int read, int fd, char *str, char *cmds);
int			checkout_cmds(int read, t_m *m);
//analize.c
int			ft_checkout(t_m *m);
void		what_is(char *str, t_m *m);
int			checkout_visual(t_m *m);
int			analize(t_m *m);
//extraction_main.c
int			one_checkout_maker(char *input, char **env, t_m *m);
int			find_type_pipe(char *cmd2);
int			enter_pipes(t_m *m, char *input, char **env);
int			ft_extractor(char *line, t_m *m);
//extraction_1.c
int			extract_alpha(const char *line, t_m *m);
int			extract_single_q(const char *line, t_m *m);
int			extract_double_q(const char *line, t_m *m);
int			extract_right(const char *line, t_m *m);
int			extract_left(const char *line, t_m *m);
//extraction_2.c
int			input_whitespace(const char *line);
int			extract_printable(const char *line, t_m *m);
int			extract_moneysign(const char *line, t_m *m);
int			extract_whitespace(const char *line, t_m *m);
int			extract_before_dollar(const char *line, t_m *m);
int			continue_extract_double_q(const char *line, t_m *m);
//extraction_3.c
int			extract_pipe(const char *line, t_m *m);
int			finish_double(const char *line, t_m *m);
int			extension_double_q(const char *line, t_m *m);
int			extension_printable(const char *line, t_m *m, int i);
//extraction_4.c
void		ft_insert_char_in_str(char *str, char ch, int position);
int			extract_single_q_sub(const char *line, t_m *m,
				char *pre_extract, int i);
int			extract_double_q_sub(const char *line, t_m *m,
				char *pre_extract, int i);
int			ft_continue_quotes_travel(const char *line, char *extract,
				int i, t_m *m);
int			money_check_on_single_q_island(char *extract, int i);
int			check_on_double_q_island(char *extract, int i);
//relst_fts.c
void		c_remove(t_list *curr, t_list *next, t_list *prev,
				int (*cmp)(void *));
void		ft_lstremove_if(t_list **lst, int (*cmp)(void *));
int			is_empty(void *content);
void		del(void *content);
//check_line.c
int			ft_signal(int read, t_m *m);
int			check_line(char *line, t_m *m);
int			extract_path(char *line);
int			line_content(char *line, t_m *m);
int			check_if(char c, t_m *m);
//quotes.c
int			quotes(char *line, t_m *m);
int			quote_checker(char *line, t_m *m);
int			if_nested(char *line);
//char_finder.c
int			ft_isquotes(int c);
int			ft_ispipe(int c);
int			ft_isredirection(int c);
int			ft_isspecialsign(int c);
int			ft_iswhitespace(int c);
// history.c
void		add_t_history(t_m *m, const char *command);
int			show_t_history(t_m *m);
void		free_t_history(t_m *m);
//comples_exec.c
char		*extract_line(int fd);
void		left_redirections(t_m *m, char *input, char **env);
int			find_type(char *file);
void		right_redirections(t_m *m, char *input, char **env);
//curses/termcap.c
void		termcap_fts(int col, int row);
void		initialize_terminal(void);
void		clear_screen_t(void);
void		move_cursor(int col, int row);
void		print_terminal_size(void);
//main.c
int			save_env(t_m *m, char **env);
//signals.c
void		signal_handler(int signal);
void		ctrl_signal_handler(int signal);
void		set_signal_handlers(t_m *m);
void		set_ctrl_signal_handlers(t_m *m);
// free
int			checkout_cmds_redirect(int read, t_m *m);
void		ft_lstclear_noalloc(t_list **lst, void (*del_noalloc)(void *));
int			find_export_data(char *str, t_m *m, int fd);
//only_redirect.c
int			checkout_redirect(int read, char *input, char **env, t_m *m);
int			close_checkoutmaker(char *last_cmd, char **env, t_m *m);
void		send_to_cmds(char *str, char **env, t_m *m);
void		send_to_cmds_cont(char *str, char **env, t_m *m);
void		continue_send_cmds(char *str, char **env, t_m *m);
#endif
