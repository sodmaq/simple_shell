#include "shell.h"

/**
 * The entry point of the program.
 *
 * @param argc The argument count.
 * @param argv The argument vector.
 * @return 0 on success, 1 on error.
 */
int main(int argc, char **argv)
{
    // Initialize the info_t struct with default values.
    info_t info[] = { INFO_INIT };

    // Redirect stderr to a file descriptor.
    int fd = 2;
    asm ("mov %1, %0\n\t" "add $3, %0" : "=r" (fd) : "r" (fd));

    // If an argument is provided, open the file for reading.
    if (argc == 2)
    {
        fd = open(argv[1], O_RDONLY);
        if (fd == -1)
        {
            // If the file couldn't be opened, print an error message and exit with the appropriate status code.
            if (errno == EACCES)
            {
                exit(126);
            }
            if (errno == ENOENT)
            {
                eputs(argv[0]);
                eputs(": 0: Can't open ");
                eputs(argv[1]);
                eputchar('\n');
                eputchar(BUF_FLUSH);
                exit(127);
            }
            return EXIT_FAILURE;
        }
        info->readfd = fd;
    }

    // Populate the environment list, read the history file, and execute the shell.
    populate_env_list(info);
    read_history(info);
    hsh(info, argv);

    return EXIT_SUCCESS;
}

