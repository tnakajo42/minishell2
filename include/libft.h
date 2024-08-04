/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:27:28 by cadenegr          #+#    #+#             */
/*   Updated: 2024/08/01 16:32:50 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define BUFFER_SIZE 1
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdbool.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <string.h>
# include <errno.h>
# include <pwd.h>

// Structs
struct	s_main;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_pipe
{
	int		error_type;
	int		path_position;
	pid_t	*pid;
	pid_t	process_id;
	pid_t	second_id_process;
	char	**cmd_arg;
	char	**path_parts;
	char	*exec_cmd;
	char	*path;
	char	*substr;
	int		fd_out;
	int		i;
	int		j;
	int		n_cmds;
	int		*fd;
	int		file;
	int		n_pipes;
}	t_p;

// Function prototypes
size_t	ft_strlen(const char *s);
void	ft_swap(int *a, int *b);
// int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strncpy(char *dst, const char *src, unsigned int n);
char	*ft_strcat(char *s1, const char *s2);
char	*ft_strncat(char *s1, const char *s2, unsigned int nb);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strchr(const char *s, int c);
int		get_index(const char *s, char c);
char	*ft_strrchr(const char *s, int c);
int		get_index_reverse(const char *s, char c);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
long	ft_atol_index(const char *s, int *counter);
long	ft_atol(char *s);
int		ft_atoi(const char *s);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memccpy(void *dst, const void *src, int c, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_calloc(size_t count, size_t size);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *str, char charset);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int nb, int fd);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void*));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void*));
int		ft_printf(const char *format, ...);
int		ft_formats(va_list args, const char format);
int		ft_putchar(int c);
int		ft_print_str(char *str);
int		ft_print_ptr(unsigned long long ptr);
int		ft_print_nbr(int n);
int		ft_print_unsigned(unsigned int n);
int		ft_print_hex(unsigned int num, const char format);
int		ft_print_percent(void);
void	ft_putstr(char *str);
void	ft_put_ptr(uintptr_t num);
int		ft_ptr_len(uintptr_t num);
char	*ft_uitoa(unsigned int n);
int		ft_num_len(unsigned	int num);
void	ft_put_hex(unsigned int num, const char format);
int		ft_hex_len(unsigned	int num);
void	ft_qsort(int arr[], int low, int high);
size_t	countword(char const *s, char c);
char	*ft_strchr_gnl(char *s, int c);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*ft_strjoin_gnl_free_second(char *s1, char *s2);
char	*ft_strnext(char *stat);
char	*ft_line(char *stat);
char	*ft_read(int fd, char *stat);
char	*get_next_line(int fd);
int		ft_strcmp(char *s1, char *s2);
void	ft_free_arr(char **arr);
char	*ft_strndup(const char *s, size_t len);
void	ft_strtrim_noret(char *s1, const char *set);
void	ft_strtrim_start_noret(char *s, size_t trim_len);
void	ft_strtrim_end_noret(char *s, size_t trim_len);
char	*ft_strtrim_start_nomodify(const char *s, size_t trim_len);
// char	*ft_strtrim_end_nomodify(char *s, size_t trim_len);
char	*ft_strtrim_start(const char *s, size_t trim_len);
char	*ft_strtrim_end(const char *s, size_t trim_len);
//exec_one_cmd
void	execute(char *cmd, char **env, t_p *p);
void	which_path(char *cmd, char **env, t_p *p);
//pipex_stuff
int		correct_argument(char **env, t_p *p);
void	init_struct(t_p *p);
void	is_error(int error_type, char *cmd);

//cmd_left_redirect.c
int		exec_and_read(char *cmd, int *type, char *file, char **env);
void	child_read(char *cmd, char *file, char **env, t_p *p);
void	child_delimiter(char *cmd, char *delimit, char **env, t_p *p);
void	child_child_delimiter(char *cmd, int *fd, char **env, t_p *p);
void	parent_delimiter(int *fd, char *delimit);

//cmd_redirect.c
void	child_one_append(char *cmd, char *file, char **env, t_p *p);
void	child_one_trunc(char *cmd, char *file, char **env, t_p *p);
int		exec_and_file(char *cmd, int *type, char *file, char **env);

//one_cmd
void	ft_access(char *cmd, t_p *p);
void	child_one_cmd(char *cmd, char **env, t_p *p);
int		exec_one_cmd(char *cmd, char **env, int *exit_status);

//pipex.c
int		pipex(char *c1, char *c2, char **env, int *exit_status);
void	parent(char *cmd, int *fd, char **env, t_p *p);
void	child(char *cmd, int *fd, char **env, t_p *p);

//file_pipex.c
int		f_pipex(char *c1, char *c2, char **env);
void	f_parent(char *cmd, int *fd, char **env, t_p *p);
void	f_child(char *cmd, int *fd, char **env, t_p *p);

//file_left_redirect.c
int		f_exec_and_read(char *cmd, int *type, char *file_delimit, char **env);
void	f_child_read(char *cmd, char *file, char **env, t_p *p);
void	f_child_delimiter(char *cmd, char *delimit, char **env, t_p *p);
void	f_child_child_delimiter(char *cmd, int *fd, char **env, t_p *p);
void	f_parent_delimiter(int *fd, char *delimit, t_p *p);
//normal_pipex.c
int		normal_pipex(char *cmd1, char *cmd2, char **env);
void	normal_child(char *cmd, int *fd, char **env, t_p *p);
void	normal_parent(char *cmd2, int *fd, char **env, t_p *p);
//only_redirect.c
int		o_exec_and_file(int type, char *file, char **env);
void	o_child_one_trunc(char *file, char **env, t_p *p);
void	o_child_one_append(char *file, char **env, t_p *p);

//super_pipex.c
void	handle_redirections(char **cmds, char **type, t_p *p);
int		enter_child(char **cmds, char **type, t_p *p, char **env);
void	super_pipes(t_p *p);
//super_files.c
void	super_trunc(char *file);
void	super_append(char *file);
int		super_pipex(char **cmd, char **type, char **env, int *exit_status);
void	super_read(char *file);
void	super_delimiter(char *delimit, int fd_out);
//super_utils.c
int		super_ft_access(char *cmd, t_p *p);
int		super_which_path(char *cmd, char **env, t_p *p);
int		super_exec_wout_execute(char *cmd, char **env, t_p *p);
int		super_execute(char *cmd, char **env, t_p *p);
//super_utils_2.c
int		how_many_pipes(char **cmds, t_p *p);
char	*get_file_from_command(char *cmd, char *symbol);
char	*extract_file(char *cmd, char *symbol);
void	close_wait(t_p *p, int *exit_status);
#endif
