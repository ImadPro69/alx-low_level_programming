#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 1024

void print_error(char *message, char *filename, int exit_code);

/**
 * main - copies the content of a file to another file
 *
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success, otherwise exit with code 97, 98, 99, or 100 on error
 */
int main(int argc, char *argv[])
{
	int fd_from, fd_to, close_from, close_to, read_bytes, write_bytes;
	char buf[BUF_SIZE];

	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}

	fd_from = open(argv[1], O_RDONLY);
	if (fd_from == -1)
		print_error("Error: Can't read from file %s\n", argv[1], 98);

	fd_to = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd_to == -1)
		print_error("Error: Can't write to file %s\n", argv[2], 99);

	while ((read_bytes = read(fd_from, buf, BUF_SIZE)) > 0)
	{
		write_bytes = write(fd_to, buf, read_bytes);
		if (write_bytes == -1)
			print_error("Error: Can't write to file %s\n", argv[2], 99);
	}

	if (read_bytes == -1)
		print_error("Error: Can't read from file %s\n", argv[1], 98);

	close_from = close(fd_from);
	if (close_from == -1)
		print_error("Error: Can't close fd %s\n", argv[1], 100);

	close_to = close(fd_to);
	if (close_to == -1)
		print_error("Error: Can't close fd %s\n", argv[2], 100);

	return (0);
}

/**
 * print_error - prints an error message to stderr
 *
 * @message: the error message format string
 * @filename: the name of the file associated with the error
 * @exit_code: the exit code to use when terminating the program
 */
void print_error(char *message, char *filename, int exit_code)
{
	dprintf(STDERR_FILENO, message, filename);
	exit(exit_code);
}

