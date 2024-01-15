/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibouchaf <ibouchaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 13:37:39 by ael-bako          #+#    #+#             */
/*   Updated: 2023/07/23 09:05:04 by ibouchaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
// # include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdarg.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/* ft_is	<ctype.h> */
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_isblank(int c);
int			ft_isspace(int c);
int			ft_isxdigit(int c);
void		ft_swap(int *a, int *b);
/* end */

/* ft_lst */
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstnew(void *content);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstiter(t_list *lst, void (*f)(void *));
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstdelone(t_list *lst, void (*del)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
/* end */

/* ft_mem */
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_calloc(size_t count, size_t size);
void		ft_bzero(void *s, size_t n);
/* end */

/* ft_put */
void		ft_putendl_fd(char *s, int fd);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
/* without fd */
void		ft_putendl(char *s);
void		ft_putchar(char c);
void		ft_putstr(char *s);
void		ft_putnbr(int n);
/* end */

/* ft_str */
char		*ft_strcat(char *s1, const char *s2);
size_t		ft_strlen_2(char **s);
int			get_long_line(char **s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_strnstr(const	char *s1, const	char *s2, size_t len);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
size_t		ft_strlcat(char *dest, const char *src, size_t size);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
char		**ft_extend_matrix(char **in, char *newstr);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_tab_replace_in(char ***big, char **small, int n);
char		*ft_strncpy(char *destination, const char *source, size_t num);
int			ft_strchars_i(const char *s, char *set);
char		*ft_strjoin(char *s1, char *s2);
int			ft_strcmp(const char *x, const char *y);
char		**ft_replace_in(char ***big, char *small, int n);
int			ft_strchr_i(const char *s, int c);
char		**ft_split(char const *s, char c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strchr(char *s, int c);
void		ft_free_tab(char ***m);
int			ft_matrixlen(char **m);
char		**ft_dup_tab(char **m);
size_t		ft_strlen(const char *str);
char		*ft_strdup(const char *s1);
char		*ft_strndup(char *str, unsigned int n);
int			ft_rcmp(char *s1, char *s2);
void		free_tab(char **error);
/* end */

/* ft_to */
int			ft_atoi(const char *str);
int			ft_toupper(int c);
int			ft_tolower(int c);
char		*ft_itoa(int n);
/* end */
int			ft_printunsigned(unsigned int n);
int			ft_printf(const char *format, ...);
int			ft_printhex(unsigned int num, const char format);
int			ft_printptr(unsigned long long ptr);
int			ft_printstr(char *str);
int			ft_printnbr(int n);
int			ft_printchar(int c);
/* end */

/* gnl */
char		*get_next_line(int fd);
char		*ft_get_line(char *str);
char		*ft_save(char *str);
char		*ft_read(int fd, char *str);
int			gnl(char **line);
/* end */
int			my_snprintf(char *str, size_t size, const char *format, ...);
#endif
