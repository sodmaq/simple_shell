#include "shell.h"

/**
 * get_environ - returns the string array copy of the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: A copy of the current environment or NULL on failure
 */
char **get_environ(info_t *info)
{
    if (!info || !info->env || info->env_changed) {
        info->environ = list_to_strings(info->env);
        info->env_changed = 0;
    }
    return (info->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: The name of the environment variable to remove
 * Return: 1 if the variable was removed, 0 otherwise
 */
int _unsetenv(info_t *info, char *var)
{
    if (!info || !info->env || !var)
        return (0);

    list_t **env = &(info->env);
    size_t i = 0;
    char *p;
    while (*env) {
        p = starts_with((*env)->str, var);
        if (p && *p == '=') {
            info->env_changed = delete_node_at_index(env, i);
            i = 0;
            continue;
        }
        *env = (*env)->next;
        i++;
    }
    return (info->env_changed);
}

/**
 * _setenv - Set or modify an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: The name of the environment variable to set
 * @value: The value to set the environment variable to
 * Return: 0 on success, 1 on failure
 */
int _setenv(info_t *info, char *var, char *value)
{
    if (!info || !info->env || !var || !value)
        return (1);

    size_t var_len = _strlen(var);
    size_t value_len = _strlen(value);
    char *buf = malloc(var_len + value_len + 2);
    if (!buf)
        return (1);
    _strcpy(buf, var);
    _strcat(buf, "=");
    _strcat(buf, value);

    list_t *env = info->env;
    char *p;
    while (env) {
        p = starts_with(env->str, var);
        if (p && *p == '=') {
            free(env->str);
            env->str = buf;
            info->env_changed = 1;
            return (0);
        }
        env = env->next;
    }
    add_node_end(&(info->env), buf, 0);
    free(buf);
    info->env_changed = 1;
    return (0);
}

