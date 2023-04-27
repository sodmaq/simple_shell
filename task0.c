#include "shell.h"

/**
 * print_numbers - prints the numbers from 0 to 9
 *
 * Return: void
 */
void print_numbers(void)
{
        int i;

        for (i = 0; i < 10; i++)
                printf("%d", i);

        printf("\n");
}

/**
 * main - Entry point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
        print_numbers();
        return (0);
}
