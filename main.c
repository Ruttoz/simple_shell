#include "shell.h"

/**
 * main - Entry point
 * @ac: To arg  count
 * @av: arg of the vector
 *
 * Return: 0 on the success, 1 on the error
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int kb = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (kb)
			: "r" (kb));

	if (ac == 2)
	{
		kb = open(av[1], O_RDONLY);
		if (kb == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = kb;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
