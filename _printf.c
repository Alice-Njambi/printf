#include "main.h"
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

#define BUFFER_SIZE 1024

/**
* _printf - A simplified printf function that handles %c, %s, %, %b, %u, %o, %x, %X, and %S specifiers.
* @format: The format string.
* @...: The values to format and print.
*
* Return: The number of characters printed (excluding the null byte).
*/
int _printf(const char *format, ...)
{
va_list args;  /* Variable argument list */
int count = 0; /* Character count */
const char *ptr; /* Pointer to traverse the format string */
char buffer[BUFFER_SIZE]; /* Buffer to store output */
int buf_index = 0; /* Index for buffer */

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
if (buf_index >= BUFFER_SIZE - 1)
{
/* Flush buffer if it's full */
write(1, buffer, buf_index);
count += buf_index;
buf_index = 0;
}
buffer[buf_index++] = ch; /* Store the character */
}
break;
case 's':
/* Print a string */
{
char *str = va_arg(args, char *); /* Get the string argument */
while (*str) /* Loop through each character in the string */
{
if (buf_index >= BUFFER_SIZE - 1)
{
/* Flush buffer if it's full */
write(1, buffer, buf_index);
count += buf_index;
buf_index = 0;
}
buffer[buf_index++] = *str; /* Store the character */
str++; /* Move to the next character */
}
}
break;
case '%':
/* Print a percent sign */
{
if (buf_index >= BUFFER_SIZE - 1)
{
/* Flush buffer if it's full */
write(1, buffer, buf_index);
count += buf_index;
buf_index = 0;
}
buffer[buf_index++] = '%'; /* Store the percent sign */
}
break;
case 'b':
/* Print an unsigned int in binary */
{
unsigned int num = va_arg(args, unsigned int);
char bin[33]; /* Buffer for binary representation */
int i;

for (i = 0; i < 32; i++)
{
bin[31 - i] = (num & (1 << i)) ? '1' : '0';
}
bin[32] = '\0';

for (i = 0; i < 32 && bin[i] == '0'; i++);
if (buf_index >= BUFFER_SIZE - 1)
{
/* Flush buffer if it's full */
write(1, buffer, buf_index);
count += buf_index;
buf_index = 0;
}
while (bin[i]) /* Skip leading zeros */
{
buffer[buf_index++] = bin[i++];
}
}
break;
case 'u':
/* Print an unsigned integer */
{
unsigned int num = va_arg(args, unsigned int);
char str[11]; /* Buffer for decimal representation */
int i = 10;

str[10] = '\0';
if (num == 0)
{
str[--i] = '0';
}
while (num > 0)
{
str[--i] = (num % 10) + '0';
num /= 10;
}

if (buf_index >= BUFFER_SIZE - (10 - i))
{
/* Flush buffer if it's full */
write(1, buffer, buf_index);
count += buf_index;
buf_index = 0;
}
while (str[i])
{
buffer[buf_index++] = str[i++];
}
}
break;
case 'o':
/* Print an unsigned integer in octal */
{
unsigned int num = va_arg(args, unsigned int);
char str[11]; /* Buffer for octal representation */
int i = 10;

str[10] = '\0';
if (num == 0)
{
str[--i] = '0';
}
while (num > 0)
{
str[--i] = (num % 8) + '0';
num /= 8;
}

if (buf_index >= BUFFER_SIZE - (10 - i))
{
/* Flush buffer if it's full */
write(1, buffer, buf_index);
count += buf_index;
buf_index = 0;
}
while (str[i])
{
buffer[buf_index++] = str[i++];
}
}
break;
case 'x':
/* Print an unsigned integer in hexadecimal (lowercase) */
{
unsigned int num = va_arg(args, unsigned int);
char str[9]; /* Buffer for hexadecimal representation */
int i = 8;

str[8] = '\0';
if (num == 0)
{
str[--i] = '0';
}
while (num > 0)
{
int digit = num % 16;
str[--i] = (digit < 10) ? (digit + '0') : (digit - 10 + 'a');
num /= 16;
}

if (buf_index >= BUFFER_SIZE - (8 - i))
{
/* Flush buffer if it's full */
write(1, buffer, buf_index);
count += buf_index;
buf_index = 0;
}
while (str[i])
{
buffer[buf_index++] = str[i++];
}
}
break;
case 'X':
/* Print an unsigned integer in hexadecimal (uppercase) */
{
unsigned int num = va_arg(args, unsigned int);
char str[9]; /* Buffer for hexadecimal representation */
int i = 8;

str[8] = '\0';
if (num == 0)
{
str[--i] = '0';
}
while (num > 0)
{
int digit = num % 16;
str[--i] = (digit < 10) ? (digit + '0') : (digit - 10 + 'A');
num /= 16;
}

if (buf_index >= BUFFER_SIZE - (8 - i))
{
/* Flush buffer if it's full */
write(1, buffer, buf_index);
count += buf_index;
buf_index = 0;
}
while (str[i])
{
buffer[buf_index++] = str[i++];
}
}
break;
case 'S':
/* Print a string with non-printable characters encoded */
{
char *str = va_arg(args, char *);
while (*str)
{
if (*str < 32 || *str >= 127)
{
/* Handle non-printable characters */
if (buf_index >= BUFFER_SIZE - 4)
{
/* Flush buffer if it's full */
write(1, buffer, buf_index);
count += buf_index;
buf_index = 0;
}
buffer[buf_index++] = '\\';
buffer[buf_index++] = 'x';
buffer[buf_index++] = (*str >> 4) + '0'; /* Upper nibble */
buffer[buf_index++] = (*str & 0x0F) + '0'; /* Lower nibble */
}
else
{
/* Handle printable characters */
if (buf_index >= BUFFER_SIZE - 1)
{
/* Flush buffer if it's full */
write(1, buffer, buf_index);
count += buf_index;
buf_index = 0;
}
buffer[buf_index++] = *str;
}
str++;
}
}
break;
default:
/* Handle unknown format specifiers */
if (buf_index >= BUFFER_SIZE - 2)
{
/* Flush buffer if it's full */
write(1, buffer, buf_index);
count += buf_index;
buf_index = 0;
}
buffer[buf_index++] = '%'; /* Store the '%' character */
buffer[buf_index++] = *ptr; /* Store the unknown specifier */
break;
}
}
else
{
/* Handle regular characters */
if (buf_index >= BUFFER_SIZE - 1)
{
/* Flush buffer if it's full */
write(1, buffer, buf_index);
count += buf_index;
buf_index = 0;
}
buffer[buf_index++] = *ptr; /* Store the character */
}
}

/* Flush remaining characters in buffer */
if (buf_index > 0)
{
write(1, buffer, buf_index);
count += buf_index;
}

va_end(args); /* Clean up the argument list */
return count; /* Return the total number of characters printed */
}
