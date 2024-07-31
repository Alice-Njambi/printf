#include "main.h"
#include <unistd.h>
#include <stdarg.h>

/**
* _printf - A simplified printf function that handles %c, %s, and %% specifiers.
* @format: The format string.
* @...: The values to format and print.
*
* Return: The number of characters printed (excluding the null byte).
*/
int _printf(const char *format, ...)
{
va_list args; /* Variable argument list */
int count = 0; /* Character count */
const char *ptr; /* Pointer to traverse the format string */

va_start(args, format); /* Initialize the argument list */

/* Loop through each character in the format string */
for (ptr = format; *ptr != '\0'; ptr++)
{
/* Check if the current character is a format specifier */
if (*ptr == '%')
{
ptr++; /* Move to the next character to determine the specifier */
switch (*ptr)
{
case 'c':
/* Print a single character */
{
char ch = (char)va_arg(args, int); /* Extract the char argument */
write(1, &ch, 1); /* Print the character */
count++; /* Increment count for each character printed */
}
break;
case 's':
/* Print a string */
{
char *str = va_arg(args, char *); /* Get the string argument */
while (*str) /* Loop through each character in the string */
{
write(1, str, 1); /* Print the character */
str++; /* Move to the next character */
count++; /* Increment count for each character printed */
}
}
break;
case '%':
/* Print a percent sign */
write(1, "%", 1);
count++; /* Increment count for the percent sign */
break;
default:
/* Handle unknown format specifiers */
write(1, "%", 1); /* Print the percent sign */
write(1, ptr, 1); /* Print the unknown specifier */
count += 2; /* Increment count for both the percent sign and specifier */
break;
}
}
else
{
/* Print regular characters */
write(1, ptr, 1); /* Print the current character */
count++; /* Increment count for each character printed */
}
}

va_end(args); /* Clean up the argument list */
return count; /* Return the total number of characters printed */
}
