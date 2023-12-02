/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 23:31:26 by svogrig           #+#    #+#             */
/*   Updated: 2023/11/28 01:28:16 by svogrig          ###   ########.fr       */
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
	write(1, format, strlen(format));
	write(1, "", 1);
	return (10);
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
			return (-1);
		len = printf("printf depuis enfant\n");
		write(pipe_len[1], &len, sizeof(int));
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
		printf("%s", buffer);
		printf("%i\n", len);
	}
	
	printf("-----------------------------\n");
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
			return (-1);
		len = ft_printf("test ft_printf\n");
		write(pipe_len[1], &len, sizeof(int));
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
		printf("%s", buffer);
		printf("%i", len);
	}
	return (0);
}


