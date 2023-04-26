#include "main.h"

/**
 * free_data - releases memory used by data structure
 *
 * @datash: pointer to data structure
 * Return: void
 */
void free_data(data_shell *datash)
{
    unsigned int i;

    for (i = 0; datash->_environ[i]; i++)
    {
        free(datash->_environ[i]);
    }

    free(datash->_environ);
    free(datash->pid);
}

/**
 * set_data - initializes data structure
 *
 * @datash: pointer to data structure
 * @av: argument vector
 * Return: void
 */
void set_data(data_shell *datash, char **av)
{
    unsigned int i;

    datash->av = av;
    datash->input = NULL;
    datash->args = NULL;
    datash->status = 0;
    datash->counter = 1;

    for (i = 0; environ[i]; i++)
        ;

    datash->_environ = malloc(sizeof(char *) * (i + 1));

    for (i = 0; environ[i]; i++)
    {
        datash->_environ[i] = _strdup(environ[i]);
    }

    datash->_environ[i] = NULL;
    datash->pid = aux_itoa(getpid());
}

/**
 * main - Entry point of the program
 *
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success
 */
int main(int ac, char **av)
{
    data_shell datash;
    (void) ac; // Avoids unused variable warning

    signal(SIGINT, get_sigint);
    set_data(&datash, av);
    shell_loop(&datash);
    free_data(&datash);

    if (datash.status < 0)
        return (255); // Returns max value of unsigned char
    else
        return (datash.status);
}

