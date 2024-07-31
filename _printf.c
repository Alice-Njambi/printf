#include "main.h"
#include <unistd.h>
#include <stdarg.h>

/**
* _printf - A simplified printf function that handles %c, %s, %%,
*           %d, %i, %b, %u, %o, %x, and %X specifiers.
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
case 'd':
case 'i':
/* Print an integer */
{
int num = va_arg(args, int); /* Extract the integer argument */
char buffer[12]; /* Buffer to hold the string representation of the integer */
int i = 0, j, is_negative = 0;

/* Handle the negative sign */
if (num < 0)
{
is_negative = 1;
num = -num;
}

/* Convert integer to string */
do {
buffer[i++] = (num % 10) + '0'; /* Extract last digit and convert to character */
num /= 10; /* Remove last digit from number */
} while (num > 0);

/* Add the negative sign if needed */
if (is_negative)
{
buffer[i++] = '-';
}

/* Reverse the buffer to get the correct number representation */
for (j = i - 1; j >= 0; j--)
{
write(1, &buffer[j], 1); /* Print each character in the buffer */
count++; /* Increment count for each character printed */
}
}
break;
case 'b':
/* Print an unsigned integer in binary */
{
unsigned int num = va_arg(args, unsigned int); /* Extract the unsigned integer argument */
char buffer[32]; /* Buffer to hold the binary representation */
int i = 0, j;

/* Handle zero case */
if (num == 0)
{
write(1, "0", 1);
count++;
continue;
}

/* Convert integer to binary */
while (num > 0)
{
buffer[i++] = (num % 2) + '0'; /* Extract last binary digit and convert to character */
num /= 2; /* Remove last binary digit */
}

/* Reverse the buffer to get the correct binary representation */
for (j = i - 1; j >= 0; j--)
{
write(1, &buffer[j], 1); /* Print each character in the buffer */
count++; /* Increment count for each character printed */
}
}
break;
case 'u':
/* Print an unsigned decimal integer */
{
unsigned int num = va_arg(args, unsigned int); /* Extract the unsigned integer argument */
char buffer[10]; /* Buffer to hold the string representation */
int i = 0, j;

/* Convert integer to string */
if (num == 0)
{
buffer[i++] = '0';
}
else
{
while (num > 0)
{
buffer[i++] = (num % 10) + '0'; /* Extract last digit and convert to character */
num /= 10; /* Remove last digit from number */
}
}

/* Reverse the buffer to get the correct number representation */
for (j = i - 1; j >= 0; j--)
{
write(1, &buffer[j], 1); /* Print each character in the buffer */
count++; /* Increment count for each character printed */
}
}
break;
case 'o':
/* Print an unsigned octal integer */
{
unsigned int num = va_arg(args, unsigned int); /* Extract the unsigned integer argument */
char buffer[11]; /* Buffer to hold the octal representation */
int i = 0, j;

/* Convert integer to octal */
if (num == 0)
{
buffer[i++] = '0';
}
else
{
while (num > 0)
{
buffer[i++] = (num % 8) + '0'; /* Extract last octal digit and convert to character */
num /= 8; /* Remove last octal digit */
}
}

/* Reverse the buffer to get the correct octal representation */
for (j = i - 1; j >= 0; j--)
{
write(1, &buffer[j], 1); /* Print each character in the buffer */
count++; /* Increment count for each character printed */
}
}
break;
case 'x':
case 'X':
/* Print an unsigned hexadecimal integer */
{
unsigned int num = va_arg(args, unsigned int); /* Extract the unsigned integer argument */
char buffer[9]; /* Buffer to hold the hexadecimal representation */
int i = 0, j;
const char *hex_chars = (*ptr == 'x') ? "0123456789abcdef" : "0123456789ABCDEF";

/* Convert integer to hexadecimal */
if (num == 0)
{
buffer[i++] = '0';
}
else
{
while (num > 0)
{
buffer[i++] = hex_chars[num % 16]; /* Extract last hex digit and convert to character */
num /= 16; /* Remove last hex digit */
}
}

/* Reverse the buffer to get the correct hexadecimal representation */
for (j = i - 1; j >= 0; j--)
{
write(1, &buffer[j], 1); /* Print each character in the buffer */
count++; /* Increment count for each character printed */
}
}
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
