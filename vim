/**
 * _strncpy - copies a string
 * @dest: the destination string to copy to
 * @src: the source string
 * @n: the number of characters to copy
 *
 * Return: pointer to the destination string
 */
char *_strncpy(char *dest, const char *src, size_t n)
{
    char *ret = dest;
    size_t i;

    for (i = 0; i < n && *src != '\0'; i++)
        *dest++ = *src++;

    while (i++ < n)
        *dest++ = '\0';

    return ret;
}

/**
 * _strncat - concatenates two strings
 * @dest: the first string
 * @src: the second string
 * @n: the maximum number of characters to concatenate
 *
 * Return: pointer to the destination string
 */
char *_strncat(char *dest, const char *src, size_t n)
{
    char *ret = dest;
    size_t dest_len = strlen(dest);

    dest += dest_len;

    for (; n > 0 && *src != '\0'; n--)
        *dest++ = *src++;

    *dest = '\0';

    return ret;
}

/**
 * _strchr - locates a character in a string
 * @s: the string to search
 * @c: the character to find
 *
 * Return: pointer to the first occurrence of the character, or NULL if not found
 */
char *_strchr(const char *s, int c)
{
    do {
        if (*s == c)
            return (char *)s;
    } while (*s++ != '\0');

    return NULL;
}

