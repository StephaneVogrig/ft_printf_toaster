/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 23:31:26 by svogrig           #+#    #+#             */
/*   Updated: 2023/12/13 05:31:02 by svogrig          ###   ########.fr       */
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

#define FILE_EXPECTED_STR "tempfile_expected_str.ft_printf_toaster"
#define FILE_EXPECTED_RETURN "tempfile_expected_return.ft_printf_toaster"


char	*file_load(char *file_path)
{
	char		*content;
	struct stat	file_attribut;
	int 		size_read;
	int			fd;


	fd = open(file_path, O_RDWR);
	fstat(fd, &file_attribut);
	content = malloc(file_attribut.st_size);
	if (!content)
		return (NULL);
	size_read = read(fd, content, file_attribut.st_size);
	close(fd);
	if (size_read == -1)
	{
		free(content);
		return (NULL);
	}
	return (content);

}

int	main(void)
{
	int		fd_expected_str;
	int		fd_expected_return;
	pid_t	child;
	int		wstatus;
	int 	size_expected;

	size_expected = 0;
	child = fork();
	if (child == 0)
	{
		fd_expected_str = open(FILE_EXPECTED_STR, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
		if (fd_expected_str == -1)
			return (-1);
		if (dup2(fd_expected_str, 1) == -1)
			return (-2);

		size_expected = printf("tempfile_expected_str cree !\n");
		close(fd_expected_str);

		fd_expected_return = open(FILE_EXPECTED_RETURN, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
		if (fd_expected_return == -1)
			return (-3);
		if (dup2(fd_expected_return, 1) == -1)
			return (-2);

		//printf("%d", fd_expected_return);
		close(fd_expected_return);
		return (0);
	}
	else
	{
		waitpid(child, &wstatus, 0);
	}

	if (WIFEXITED(wstatus))
	{
		if (WEXITSTATUS(wstatus) != 0)
			return (-4);
	}
	else
		return (-5);
	












	char *expected_str = file_load(FILE_EXPECTED_STR);
	char *expected_return = file_load(FILE_EXPECTED_RETURN);
	
	printf("expected stdout = %s\n", expected_str);
	printf("expected return = %s\n", expected_return);

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
