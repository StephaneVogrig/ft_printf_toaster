/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 23:31:26 by svogrig           #+#    #+#             */
/*   Updated: 2023/11/21 12:57:27 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <unistd.h>
//# include <stdbool.h>
//# include <ctype.h>
//# include <string.h>
//# include <bsd/string.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdlib.h>
//# include <time.h>
//# include <stdarg.h>
#include <sys/types.h>
#include <sys/wait.h>

int	main(void)
{
	int		fd_tempfile;
	pid_t	child;
	int dup_stdout;
	int wstatus;

	dup_stdout = 1;
	child = fork();
	int size;

	size = 0;
	if (child == 0)
	{
		fd_tempfile = open("tempfile.printftoaster", O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
		if (fd_tempfile == -1)
		{
			printf("fichier temporaire non cree !\n");
			return (-1);
		}
		int dup_stdout = dup(1);
		if (dup2(fd_tempfile, 1) == -1)
			return (-1);
		size = printf("fichier temporaire cree !\n");
		close(fd_tempfile);
		return (0);
	}
	else
	{
		waitpid(child, &wstatus, 0);
	}

	char		*content;
	struct stat	file_attribut;
	int size_read;

	fd_tempfile = open("tempfile.printftoaster", O_RDWR);
	fstat(fd_tempfile, &file_attribut);
	content = malloc(file_attribut.st_size);
	if (!content)
		return (-1);
	size_read = read(fd_tempfile, content, file_attribut.st_size);
	close(fd_tempfile);
	printf("size in file : %ld, size read : %d\n", file_attribut.st_size, size_read);
	write(1, content, file_attribut.st_size);
	//write(dup_stdout, "content\n", 7);
	//write(dup_stdout, content, size);
/*	

	//sleep(3);

	
	//lseek(fd_tempfile, 0, SEEK_SET);
	*(content + size) = '\0';
	//dup2(dup_stdout, 1);
	//write(dup_stdout, "content", 7);
	if (size == 0)
	{
		write(dup_stdout, "0", 1);
	}
	write(dup_stdout, content, 10);
	printf("fichier temporaire ferme !\n");
	unlink("tempfile.printftoaster");
	printf("fichier temporaire efface !\n");
*/	return (0);
}

char	*file_content_to_str(int fd)
{
	struct stat	file_attribut;
	char		*content;

	fstat(fd, &file_attribut);
	content = malloc(file_attribut.st_size + 1);
	if (!content)
		return (NULL);
	lseek(fd, 0, SEEK_SET);
	read(fd, content, file_attribut.st_size);
	*(content + file_attribut.st_size) = '\0';
	return (content);
}
