/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:17:14 by khanadat          #+#    #+#             */
/*   Updated: 2025/07/20 17:33:13 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
// #ifndef BUFFER_SIZE
// # define BUFFER_SIZE 42
// #endif

// typedef struct s_gnl
// {
// 	char		*str;
// 	ptrdiff_t	head;
// 	ptrdiff_t	tail;
// }	t_gnl;

#define ERR_MALLOC -2
#define ERR_READ -1
#define GNL_EOF 0
#define GNL_LINE 1
#define NL_FOUND 1
#define NL_NOT 0

static int	free_return(char **str, int output);
static int	find_nl(t_gnl *gnl);
static int	read_to_str(int fd, t_gnl *gnl);
static char	*get_line(t_gnl *gnl);

//set fd = GNL_FREE_FD and you can free(gnl.str)
int	ft_get_next_line(int fd, char **line)
{
	static t_gnl	gnl = {NULL, 0, -1};
	int				rd;

	if (!gnl.str)
		gnl.str = ft_strdup("");
	if (!gnl.str)
		return (ERR_MALLOC);
	if (fd == GNL_FREE_FD)
		return (free_return (&gnl.str, GNL_EOF));
	rd = read_to_str(fd, &gnl);
	if (rd < 0)
		return (rd);
	if (rd == 0 && (!gnl.str || !gnl.str[gnl.head]))
		return (free_return (&gnl.str, GNL_EOF));
	*line = get_line(&gnl);
	if (*line)
		return (GNL_LINE);
	return (ERR_MALLOC);
}

static int	free_return(char **str, int output)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
	return (output);
}

static int	find_nl(t_gnl *gnl)
{
	ptrdiff_t	i;

	i = gnl->tail;
	while (gnl->str[++i])
	{
		if (gnl->str[i] == '\n')
		{
			gnl->tail = i;
			return (NL_FOUND);
		}
	}
	return (NL_NOT);
}

static int	read_to_str(int fd, t_gnl *gnl)
{
	int		rd;
	char	*tmp;
	char	*buf;

	rd = 1;
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (free_return(&gnl->str, ERR_MALLOC));
	while (!find_nl(gnl) && rd > 0)
	{
		rd = read(fd, buf, BUFFER_SIZE);
		if (rd < 0)
			return (free(buf), free_return(&gnl->str, ERR_READ));
		buf[rd] = '\0';
		tmp = gnl->str;
		gnl->str = ft_strjoin(tmp, buf);
		free(tmp);
		if (!gnl->str)
			return (free_return(&buf, ERR_MALLOC));
	}
	if (!gnl->str)
		return (free_return(&buf, ERR_MALLOC));
	return (free_return(&buf, rd));
}

static char	*get_line(t_gnl *gnl)
{
	char	*line;

	line = ft_strndup(gnl->str + gnl->head, gnl->tail - gnl->head + 1);
	gnl->head = gnl->tail + 1;
	return (line);
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
