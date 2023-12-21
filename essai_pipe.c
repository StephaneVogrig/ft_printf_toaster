/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   essai_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 23:31:26 by svogrig           #+#    #+#             */
/*   Updated: 2023/12/13 05:13:45 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <unistd.h>
//# include <stdbool.h>
//# include <ctype.h>
# include <string.h>
//# include <bsd/string.h>
//# include <fcntl.h>
//# include <sys/stat.h>
//# include <stdlib.h>
//# include <time.h>
//# include <stdarg.h>
//#include <sys/types.h>
#include <sys/wait.h>

int	ft_printf(char *format)
{
	//write(1, format, strlen(format));
	//write(1, "\n", 1);
	return (write(1, format, strlen(format)));
}

int	prepare(int *pipe_str, int *pipe_len)
{
	close(pipe_str[0]);
	close(pipe_len[0]);
	if (dup2(pipe_str[1], 1) == -1)
	{
		close(pipe_str[1]);
		close(pipe_len[1]);
		return (0);
	}
	return (1);
}

int	main(void)
{
	int		pipe_str[2];
	int		pipe_len[2];
	pid_t	child;
	int		wstatus;
	int		len;
	char buffer[8192];

	if(pipe(pipe_str) == -1)
		return (-1);
	if(pipe(pipe_len) == -1)
		return (-1);
	
	child = fork();
	if (child == 0)
	{	
		close(pipe_str[0]);
		close(pipe_len[0]);
		if (dup2(pipe_str[1], 1) == -1)
		{
			close(pipe_str[1]);
			close(pipe_len[1]);
			return (-1);
		}
		len = printf("123456789123456789");
		write(pipe_len[1], &len, sizeof(int));
		close(pipe_str[1]);
		close(pipe_len[1]);
		return (0);
	}
	else
	{
		waitpid(child, &wstatus, 0);
		close(pipe_str[1]);
		close(pipe_len[1]);
		read(pipe_str[0], buffer, 8192);
		read(pipe_len[0], &len, sizeof(int));
		close(pipe_str[0]);
		close(pipe_len[0]);
		printf("%s | ", buffer);
		printf("%i\n", len);
	}
	
	//printf("-----------------------------\n");
	if(pipe(pipe_str) == -1)
		return (-1);
	if(pipe(pipe_len) == -1)
		return (-1);
	
	child = fork();
	if (child == 0)
	{	
		close(pipe_str[0]);
		close(pipe_len[0]);
		if (dup2(pipe_str[1], 1) == -1)
		{
			close(pipe_str[1]);
			close(pipe_len[1]);
			return (-1);
		}
		len = ft_printf("test ft_printf");
		write(pipe_len[1], &len, sizeof(int));
		close(pipe_str[1]);
		close(pipe_len[1]);
		return (0);
	}
	else
	{
		waitpid(child, &wstatus, 0);
		close(pipe_str[1]);
		close(pipe_len[1]);
		read(pipe_str[0], buffer, 8192);
		read(pipe_len[0], &len, sizeof(int));
		close(pipe_str[0]);
		close(pipe_len[0]);
		printf("%s | ", buffer);
		printf("%i\n", len);
	}
	return (0);
}


