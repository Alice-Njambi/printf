#include "main.h"
#include <unistd.h>
#include <stdarg.h>
#include <string.h>

#define BUFFER_SIZE 1024

/**
* _printf - A simplified printf function that handles various specifiers.
* @format: The format string.
* @...: The values to format and print.
*
* Return: The number of characters printed (excluding the null byte).
*/
int _printf(const char *format, ...)
{
va_list args; /* Variable argument list */
char buffer[BUFFER_SIZE]; /* Buffer to accumulate characters */
int count = 0; /* Total characters printed */
int buf_index = 0; /* Current index in the buffer */
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
{
/* Print a single character */
if (buf_index >= BUFFER_SIZE - 1)
{
/* Flush buffer if it's full */
write(1, buffer, buf_index);
count += buf_index;
buf_index = 0;
}
buffer[buf_index++] = (char)va_arg(args, int); /* Extract and store the char argument */
break;
}
case 's':
{
/* Print a string */
char *str = va_arg(args, char *); /* Get the string argument */
while (*str)
{
if (buf_index >= BUFFER_SIZE - 1)
{
/* Flush buffer if it's full */
write(1, buffer, buf_index);
count += buf_index;
buf_index = 0;
}
buffer[buf_index++] = *str++; /* Store each character from the string */
}
break;
}
case '%':
{
/* Print a percent sign */
if (buf_index >= BUFFER_SIZE - 1)
{
/* Flush buffer if it's full */
write(1, buffer, buf_index);
count += buf_index;
buf_index = 0;
}
buffer[buf_index++] = '%'; /* Store the percent sign */
break;
}
case 'd':
case 'i':
{
/* Print an integer */
int num = va_arg(args, int); /* Extract the integer argument */
char num_buffer[12]; /* Buffer to hold the integer string representation */
int i = 0, j;
int is_negative = 0;

/* Handle the negative sign */
if (num < 0)
{
is_negative = 1;
num = -num;
}

/* Convert integer to string */
do {
num_buffer[i++] = (num % 10) + '0'; /* Extract last digit */
num /= 10; /* Remove last digit */
} while (num > 0);

/* Add the negative sign if needed */
if (is_negative)
{
num_buffer[i++] = '-';
}

/* Reverse the buffer and store in the main buffer */
for (j = i - 1; j >= 0; j--)
{
if (buf_index >= BUFFER_SIZE - 1)
{
/* Flush buffer if it's full */
write(1, buffer, buf_index);
count += buf_index;
buf_index = 0;
}
buffer[buf_index++] = num_buffer[j];
}
break;
}
case 'b':
{
/* Print an unsigned integer in binary */
unsigned int num = va_arg(args, unsigned int); /* Extract the unsigned integer argument */
char num_buffer[33]; /* Buffer to hold the binary representation */
int i = 0, j;

/* Handle zero case */
if (num == 0)
{
if (buf_index >= BUFFER_SIZE - 1)
{
/* Flush buffer if it's full */
write(1, buffer, buf_index);
count += buf_index;
buf_index = 0;
}
buffer[buf_index++] = '0';
}
else
{
while (num > 0)
{
num_buffer[i++] = (num % 2) + '0'; /* Extract last binary digit */
num /= 2; /* Remove last binary digit */
}

/* Reverse the buffer and store in the main buffer */
for (j = i - 1; j >= 0; j--)
{
if (buf_index >= BUFFER_SIZE - 1)
{
/* Flush buffer if it's full */
write(1, buffer, buf_index);
count += buf_index;
buf_index = 0;
}
buffer[buf_index++] = num_buffer[j];
}
}
break;
}
case 'u':
{
/* Print an unsigned decimal integer */
unsigned int num = va_arg(args, unsigned int); /* Extract the unsigned integer argument */
char num_buffer[11]; /* Buffer to hold the decimal representation */
int i = 0, j;

/* Convert integer to string */
if (num == 0)
{
if (buf_index >= BUFFER_SIZE - 1)
{
/* Flush buffer if it's full */
write(1, buffer, buf_index);
count += buf_index;
buf_index = 0;
}
buffer[buf_index++] = '0';
}
else
{
while (num > 0)
{
num_buffer[i++] = (num % 10) + '0'; /* Extract last digit */
num /= 10; /* Remove last digit */
}

/* Reverse the buffer and store in the main buffer */
for (j = i - 1; j >= 0; j--)
{
if (buf_index >= BUFFER_SIZE - 1)
{
/* Flush buffer if it's full */
write(1, buffer, buf_index);
count += buf_index;
buf_index = 0;
}
buffer[buf_index++] = num_buffer[j];
}
}
break;
}
case 'o':
{
/* Print an unsigned octal integer */
unsigned int num = va_arg(args, unsigned int); /* Extract the unsigned integer argument */
char num_buffer[11]; /* Buffer to hold the octal representation */
int i = 0, j;

/* Convert integer to octal */
if (num == 0)
{
if (buf_index >= BUFFER_SIZE - 1)
{
/* Flush buffer if it's full */
write(1, buffer, buf_index);
count += buf_index;
buf_index = 0;
}
buffer[buf_index++] = '0';
}
else
{
while (num > 0)
{
num_buffer[i++] = (num % 8) + '0'; /* Extract last octal digit */
num /= 8; /* Remove last octal digit */
}

/* Reverse the buffer and store in the main buffer */
for (j = i - 1; j >= 0; j--)
{
if (buf_index >= BUFFER_SIZE - 1)
{
/* Flush buffer if it's full */
write(1, buffer, buf_index);
count += buf_index;
buf_index = 0;
}
buffer[buf_index++] = num_buffer[j];
}
}
break;
}
case 'x':
case 'X':
{
/* Print an unsigned hexadecimal integer */
unsigned int num = va_arg(args, unsigned int); /* Extract the unsigned integer argument */
char num_buffer[9]; /* Buffer to hold the hexadecimal representation */
int i = 0, j;
const char *hex_chars = (*ptr == 'x') ? "0123456789abcdef" : "0123456789ABCDEF";

/* Convert integer to hexadecimal */
if (num == 0)
{
if (buf_index >= BUFFER_SIZE - 1)
{
/* Flush buffer if it's full */
write(1, buffer, buf_index);
count += buf_index;
buf_index = 0;
}
buffer[buf_index++] = '0';
}
else
{
while (num > 0)
{
num_buffer[i++] = hex_chars[num % 16]; /* Extract last hex digit */
num /= 16; /* Remove last hex digit */
}

/* Reverse the buffer and store in the main buffer */
for (j = i - 1; j >= 0; j--)
{
if (buf_index >= BUFFER_SIZE - 1)
{
/* Flush buffer if it's full */
write(1, buffer, buf_index);
count += buf_index;
buf_index = 0;
}
buffer[buf_index++] = num_buffer[j];
}
}
break;
}
default:
{
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
buffer[buf_index++] = *ptr; /* Store the regular character */
}
}

/* Flush any remaining characters in the buffer */
if (buf_index > 0)
{
write(1, buffer, buf_index);
count += buf_index;
}

va_end(args); /* Clean up the argument list */
return count; /* Return the total number of characters printed */
}

