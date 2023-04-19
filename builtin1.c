#include "shell.h"

/**
 * print_history - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int print_history(info_t *info)
{
    print_list(info->history);
    return (0);
}

/**
 * remove_alias - removes an alias from the list
 * @info: parameter struct
 * @alias: the alias to remove
 *
 * Return: Always 0 on success, 1 on error
 */
int remove_alias(info_t *info, char *alias)
{
    char *p, c;
    int ret;

    p = _strchr(alias, '=');
    if (!p)
        return (1);
    c = *p;
    *p = 0;
    ret = delete_node_at_index(&(info->alias),
        get_node_index(info->alias, node_starts_with(info->alias, alias, -1)));
    *p = c;
    return (ret);
}

/**
 * set_alias - sets an alias to a command
 * @info: parameter struct
 * @alias: the alias to set
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *alias)
{
    char *p;

    p = _strchr(alias, '=');
    if (!p)
        return (1);
    if (!*++p)
        return (remove_alias(info, alias));

    remove_alias(info, alias);
    return (add_node_end(&(info->alias), alias, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
    char *p = NULL, *alias = NULL;

    if (node)
    {
        p = _strchr(node->str, '=');
        for (alias = node->str; alias <= p; alias++)
            _putchar(*alias);
        _putchar('\'');
        _puts(p + 1);
        _puts("'\n");
        return (0);
    }
    return (1);
}

/**
 * alias_command - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int alias_command(info_t *info)
{
    int i = 0;
    char *p = NULL;
    list_t *node = NULL;

    if (info->argc == 1)
    {
        node = info->alias;
        while (node)
        {
            print_alias(node);
            node = node->next;
        }
        return (0);
    }
    for (i = 1; info->argv[i]; i++)
    {
        p = _strchr(info->argv[i], '=');
        if (p)
            set_alias(info, info->argv[i]);
        else
            print_alias(node_starts_with(info->alias, info->argv[i], '='));
    }

    return (0);
}

