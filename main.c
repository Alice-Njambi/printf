#include <limits.h>
#include <stdio.h>
#include "main.h"

/**
* main - Entry point of the program.
*
* Return: Always 0 (Success)
*/
int main(void)
{
int len;         /* Variable to store the length of output from _printf */
int len2;        /* Variable to store the length of output from printf */
unsigned int ui; /* Variable to store an unsigned integer value */
void *addr;      /* Variable to store a pointer address */

/* Test _printf with a simple sentence and store the output length */
len = _printf("Let's try to printf a simple sentence.\n");

/* Test printf with a simple sentence and store the output length */
len2 = printf("Let's try to printf a simple sentence.\n");

/* Initialize ui with a large unsigned integer value */
ui = (unsigned int)INT_MAX + 1024;

/* Initialize addr with a specific pointer address */
addr = (void *)0x7ffe637541f0;

/* Test _printf with different format specifiers and print lengths */
_printf("Length:[%d, %i]\n", len, len); /* Test with %d and %i specifiers */
printf("Length:[%d, %i]\n", len2, len2); /* Compare with printf output */

_printf("Negative:[%d]\n", -762534); /* Test with negative integer */
printf("Negative:[%d]\n", -762534); /* Compare with printf output */

_printf("Unsigned:[%u]\n", ui); /* Test with unsigned integer */
printf("Unsigned:[%u]\n", ui); /* Compare with printf output */

_printf("Unsigned octal:[%o]\n", ui); /* Test with unsigned octal */
printf("Unsigned octal:[%o]\n", ui); /* Compare with printf output */

_printf("Unsigned hexadecimal:[%x, %X]\n", ui, ui); /* Test with unsigned hexadecimal */
printf("Unsigned hexadecimal:[%x, %X]\n", ui, ui); /* Compare with printf output */

_printf("Character:[%c]\n", 'H'); /* Test with a single character */
printf("Character:[%c]\n", 'H'); /* Compare with printf output */

_printf("String:[%s]\n", "I am a string !"); /* Test with a string */
printf("String:[%s]\n", "I am a string !"); /* Compare with printf output */

_printf("Address:[%p]\n", addr); /* Test with a pointer address */
printf("Address:[%p]\n", addr); /* Compare with printf output */

_printf("Percent:[%%]\n"); /* Test with percent sign */
len = _printf("Len:[%d]\n", len); /* Print length returned by _printf */
len2 = printf("Len:[%d]\n", len2); /* Print length returned by printf */

return (0); /* Return success code */
}

