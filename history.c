#include "shell.h"

/**
 * read_input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t read_input_buf(info_t *info, char **buf, size_t *len)
{
    ssize_t read_bytes = 0;
    size_t len_p = 0;

    if (!*len)
    {
        free(*buf);
        *buf = NULL;
        signal(SIGINT, handle_sigint);
#if USE_GETLINE
        read_bytes = getline(buf, &len_p, stdin);
#else
        read_bytes = get_line(info, buf, &len_p);
#endif
        if (read_bytes > 0)
        {
            if ((*buf)[read_bytes - 1] == '\n')
            {
                (*buf)[read_bytes - 1] = '\0';
                read_bytes--;
            }
            info->linecount_flag = 1;
            remove_comments(*buf);
            build_history_list(info, *buf, info->histcount++);
            if (_strchr(*buf, ';'))
            {
                *len = read_bytes;
                info->cmd_buf = buf;
            }
        }
    }
    return (read_bytes);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
    static char *buf;
    static size_t i, j, len;
    ssize_t read_bytes = 0;
    char **buf_p = &(info->arg), *p;

    _putchar(BUF_FLUSH);
    read_bytes = read_input_buf(info, &buf, &len);
    if (read_bytes == -1)
        return (-1);
    if (len)
    {
        j = i;
        p = buf + i;

        check_chain(info, buf, &j, i, len);
        while (j < len)
        {
            if (is_chain(info, buf, &j))
                break;
            j++;
        }

        i = j + 1;
        if (i >= len)
        {
            i = len = 0;
            info->cmd_buf_type = CMD_NORM;
        }

        *buf_p = p;
        return (_strlen(p));
    }

    *buf_p = buf;
    return (read_bytes);
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: read_bytes
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
    ssize_t read_bytes = 0;

    if (*i)
        return (0);
    read_bytes = read(info->readfd, buf, READ_BUF_SIZE);
    if (read_bytes >= 0)
        *i = read_bytes;
    return (read_bytes);
}

/**
 * get_line - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: read_bytes
 */
int get_line(info_t *info, char **ptr, size_t *length)
{
    static char buf[READ_BUF_SIZE];
    static size_t i, len;
    size_t k;
    ssize_t read_bytes = 0, total_bytes = 0;
    char *p =

