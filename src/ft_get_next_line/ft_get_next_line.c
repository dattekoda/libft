/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:17:14 by khanadat          #+#    #+#             */
/*   Updated: 2026/05/10 19:45:17 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <unistd.h>
#include <stdlib.h>

#define SUCCESS 0

static ssize_t	append_store(int fd, char **store);
static int		substr_line(
					char **line,
					const char *store,
					const char *end_line);
static int		update_store(char **store, const char *end_line);
static void		safe_free(char **ptr);

int	ft_get_next_line(int fd, char **line)
{
	static char	*store = NULL;
	ssize_t		read_size;
	char		*end_line;

	if (fd == STORE_FREE_FD)
		safe_free(&store);
	if (!line || fd < 0 || BUFFER_SIZE <= 0)
		return (GNL_ERR);
	*line = NULL;
	read_size = append_store(fd, &store);
	if (read_size < 0 || (read_size == 0 && (!store || !store[0])))
		return (safe_free(&store), read_size);
	end_line = ft_strchr(store, '\n');
	if (substr_line(line, store, end_line))
		return (safe_free(&store), GNL_ERR);
	if (update_store(&store, end_line))
		return (safe_free(&store), safe_free(line), GNL_ERR);
	return (GNL_LINE);
}

static ssize_t	append_store(int fd, char **store)
{
	char	buf[BUFFER_SIZE + 1];
	char	*tmp;
	ssize_t	read_size;

	if (!*store)
		*store = ft_strdup("");
	if (!*store)
		return (GNL_ERR);
	read_size = 1;
	while (!ft_strchr(*store, '\n') && read_size > 0)
	{
		read_size = read(fd, buf, BUFFER_SIZE);
		if (read_size <= 0)
			break ;
		buf[read_size] = '\0';
		tmp = ft_strjoin(*store, buf);
		safe_free(store);
		if (!tmp)
			return (GNL_ERR);
		*store = tmp;
	}
	return (read_size);
}

static int	substr_line(char **line, const char *store, const char *end_line)
{
	if (end_line)
		*line = ft_strndup(store, end_line - store + 1);
	else
		*line = ft_strdup(store);
	if (!*line)
		return (GNL_ERR);
	return (SUCCESS);
}

static int	update_store(char **store, const char *end_line)
{
	char	*tmp;

	if (end_line)
	{
		tmp = ft_strdup(end_line + 1);
		if (!tmp)
			return (GNL_ERR);
		safe_free(store);
		*store = tmp;
	}
	else
		safe_free(store);
	return (SUCCESS);
}

static void	safe_free(char **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

// #include <stdio.h>
// #include <fcntl.h>
// int	main(int argc, char *argv[])
// {
// 	char	*line;
// 	int		gnl;
// 	int		fd;
// 	if (argc != 2)
// 		return (1);
// 	fd = open(argv[1], O_RDONLY);
// 	gnl = 1;
// 	while (gnl > 0)
// 	{
// 		gnl = ft_get_next_line(fd, &line);
// 		if (gnl < 0)
// 			break ;
// 		printf("gnl = %d\n%s", gnl, line);
// 		free(line);
// 	}
// 	ft_get_next_line(-7, NULL);
// 	close(fd);
// 	return (0);
// }

// #include <stdio.h>
// #include <fcntl.h>
// int	main(int argc, char *argv[])
// {
// 	char	*line;
// 	int		gnl;
// 	int		fd;
// 	gnl = 1;
// 	while (gnl > 0)
// 	{
// 		gnl = ft_get_next_line(STDIN_FILENO, &line);
// 		if (gnl < 0)
// 			break ;
// 		if (gnl == 0)
// 			break ;
// 		printf("%d, %s", gnl, line);
// 		free(line);
// 	}
// 	return (0);
// }
