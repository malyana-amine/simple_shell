#include "shell.h"

/**
 * er_conv - Convert a string to an integer with error handling.
 * @stri: Pointer to the input string.
 *
 * Return: The converted integer value or -1 on error.
 */
int er_conv(char *stri)
{
	int i = 0;
	unsigned long int s = 0;

	if (*stri == '+')
		stri++;
	for (i = 0;  stri[i] != '\0'; i++)
	{
		if (stri[i] >= '0' && stri[i] <= '9')
		{
			s *= 10;
			s += (stri[i] - '0');
			if (s > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (s);
}

/**
 * er_print - Print error message to stderr.
 * @in: Pointer to infocmd struct.
 * @stri: Error message string.
 *
 * Return: None.
 */
void er_print(infocmd *in, char *stri)
{
	er_puts(in->fname);
	er_puts(": ");
	fct_decimal(in->line_count, STDERR_FILENO);
	er_puts(": ");
	er_puts(in->argv[0]);
	er_puts(": ");
	er_puts(stri);
}

/**
 * fct_decimal - Print an integer in decimal format.
 * @pt: Integer to be printed.
 * @file: File descriptor to write to.
 *
 * Return: Number of characters printed.
 */
int fct_decimal(int pt, int file)
{
	int (*__put_char)(char) = _put_char;
	int i, ct = 0;
	unsigned int _abs_, c;

	if (file == STDERR_FILENO)
		__put_char = e_put_char;
	if (pt < 0)
	{
		_abs_ = -pt;
		__put_char('-');
		ct++;
	}
	else
		_abs_ = pt;
	c = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__put_char('0' + c / i);
			ct++;
		}
		c %= i;
	}
	__put_char('0' + c);
	ct++;

	return (ct);
}

/**
 * conv_number - Convert a number to a specified base and format.
 * @num: Number to be converted.
 * @b: Base for conversion (e.g., 16 for hexadecimal).
 * @fl: Conversion format flags.
 *
 * Return: Pointer to the converted number string.
 */
char *conv_number(long int num, int b, int fl)
{
	static char *ar;
	static char bfr[50];
	char s = 0;
	char *poiter;
	unsigned long n = num;

	if (!(fl & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		s = '-';

	}
	ar = fl & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	poiter = &bfr[49];
	*poiter = '\0';

	do	{
		*--poiter = ar[n % b];
		n /= b;
	} while (n != 0);

	if (s)
		*--poiter = s;
	return (poiter);
}

/**
 * fct_remove - Remove comments from a string buffer.
 * @bfr: Input string bfr to process.
 *
 * Return: None.
 */
void fct_remove(char *bfr)
{
	int i;

	for (i = 0; bfr[i] != '\0'; i++)
		if (bfr[i] == '#' && (!i || bfr[i - 1] == ' '))
		{
			bfr[i] = '\0';
			break;
		}
}
