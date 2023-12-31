/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:22:15 by vdenisse          #+#    #+#             */
/*   Updated: 2023/04/26 12:33:13 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

size_t	increase_buffer(char **old_buffer, int fd);
int		reduce_buffer(char **old_buffer, size_t buffer_size, int bytes_read);
int		ft_read(char **new_read, int fd);
char	*get_next_line(int fd);
size_t	ft_strlen(const char *str);
size_t	ft_strcat(char *dst, const char *src);
int		ft_strchr(const char *s, char c);
size_t	ft_strcpy(char *dst, const char *src, size_t n);
int		ft_substr(char const *s, char **substr, unsigned int start, size_t len);
int		ft_extract_line(char **next_line, char **saved, size_t s_size, int b);
#endif
