

<h1 align="center">
	42cursus' libft
</h1>

<p align="center">
	<b><i>Development repo for 42cursus' libft project</i></b><br>
	For further information about 42cursus and its projects, please refer to <a href="https://github.com/Aelbakouri/1337_cursus"><b>42cursus repo</b></a>.
</p>

<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/Aelbakouri/libft?color=blueviolet" />
	<img alt="Number of lines of code" src="https://img.shields.io/tokei/lines/github/Aelbakouri/libft?color=blueviolet" />
	<img alt="Code language count" src="https://img.shields.io/github/languages/count/Aelbakouri/libft?color=blue" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/Aelbakouri/libft?color=blue" />
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/Aelbakouri/libft?color=brightgreen" />
</p>

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/a7ea133692384ce898799f497288e766)](https://app.codacy.com/gh/Aelbakouri/libft?utm_source=github.com&utm_medium=referral&utm_content=Aelbakouri/libft&utm_campaign=Badge_Grade_Settings)
![norminette](https://github.com/hassansaadfr/so_long/workflows/norminette3/badge.svg)



---

## 🗣️ About

> _The aim of this project is to code a C library regrouping usual functions that you'll be allowed to use in all your other projects._

For detailed information, refer to the [**subject of this project**](https://github.com/appinha/42cursus/tree/master/_PDFs).

	🚀 TLDR: this project consists of coding basic C functions (see below), which are then compiled
	into a library for use in other projects of the cursus.

## Directory Hierarchy
```bash
|—— Makefile
|—— inc
|    |—— libft.h
|—— pdf
|    |—— en.subject.pdf
|—— srcs
|    |—— ft_is
|        |—— ft_isalnum.c		//alphanumeric character test.
|        |—— ft_isalpha.c		// alphabetic character test.
|        |—— ft_isascii.c		// test for ASCII character.
|        |—— ft_isblank.c		// space or tab character test.
|        |—— ft_isdigit.c		// decimal-digit character test
|        |—— ft_isprint.c		//  printing character test (space character inclusive).
|        |—— ft_isspace.c		// white-space character test.
|        |—— ft_isxdigit.c		// hexadecimal-digit character test
|        |—— ft_swap.c			// swap value of two integers.
|    |—— ft_lst
|        |—— ft_lstadd_back_bonus.c	// add new element at end of list.
|        |—— ft_lstadd_front_bonus.c	// add new element at beginning of list.
|        |—— ft_lstclear_bonus.c	// delete sequence of elements of list from a starting point.
|        |—— ft_lstdelone_bonus.c	// delete element from list.
|        |—— ft_lstiter_bonus.c		// apply function to content of all lists elements.
|        |—— ft_lstlast_bonus.c		// find last element of list.
|        |—— ft_lstmap_bonus.c		// apply function to content of all lists elements into new list.
|        |—— ft_lstnew_bonus.c		// create new list.
|        |—— ft_lstsize_bonus.c		// count elements of a list.
|    |—— ft_mem
|        |—— ft_bzero.c			// write zeroes to a byte string.
|        |—— ft_calloc.c		//  memory allocation.
|        |—— ft_memchr.c		// locate byte in byte string.
|        |—— ft_memcmp.c		// compare byte string.
|        |—— ft_memcpy.c		// copy memory area.
|        |—— ft_memmove.c		// copy byte string.
|        |—— ft_memset.c		// write a byte to a byte string.
|    |—— ft_put
|        |—— ft_putchar.c		// output a character to stdout.
|        |—— ft_putchar_fd.c		// output a character to given file.
|        |—— ft_putendl.c		// output string to stdout with newline.
|        |—— ft_putendl_fd.c		// output string to given file with newline.
|        |—— ft_putnbr.c		//  output integer to stdout.
|        |—— ft_putnbr_fd.c		// output integer to given file.
|        |—— ft_putstr.c		// output string to s	tdout.
|        |—— ft_putstr_fd.c		// output string to given file.
|    |—— ft_str
|        |—— ft_split.c			// split string, with specified character as delimiter, into an array of strings.
|        |—— ft_strcat.c		// concatenate strings (s2 into s1).
|        |—— ft_strchr.c		// locate character in string (first occurrence).
|        |—— ft_strdup.c		// save a copy of a string (with malloc).
|        |—— ft_striteri.c		// modifying string with specified function.
|        |—— ft_strjoin.c		// concatenate two strings into a new string (with malloc).
|        |—— ft_strlcat.c		//  size-bounded string concatenation.
|        |—— ft_strlcpy.c		// size-bounded string copying.
|        |—— ft_strlen.c		// find length of string.
|        |—— ft_strlen_2.c		// find length of 2D array (i.e. splitted string).
|        |—— ft_strmapi.c		// create new string from modifying string with specified function.
|        |—— ft_strncmp.c		// compare strings (size-bounded).
|        |—— ft_strndup.c		// save a copy of a string (with malloc, size-bounded).
|        |—— ft_strnstr.c		// locate a substring in a string (size-bounded).
|        |—— ft_strrchr.c		// locate character in string (last occurence).
|        |—— ft_strtrim.c		// trim beginning and end of string with the specified characters.
|        |—— ft_substr.c		// extract substring from string.
|    |—— ft_to
|        |—— ft_atoi.c			// convert ASCII string to integer.
|        |—— ft_itoa.c			// convert integer to ASCII string.
|        |—— ft_tolower.c		// upper case to lower case letter conversion.
|        |—— ft_toupper.c		// lower case to upper case letter conversion.
|    |—— gnl
|        |—— get_next_line.c		// return a line from given fd
|        |—— gnl.c			// read from standard input and return line
|    |—— printf
|        |—— ft_printf.c		// function takes a format string as its first argument, followed by a set of variables
|        |—— ft_printhex.c		// print hexadecimal format %x and %X
|        |—— ft_printptr.c		// print the address format %p
|        |—— ft_printunsigned.c		// %u unsigned int
|        |—— ft_utils.c
```

##  Usage

### Requirements

The library is written in C language and thus needs the **`gcc` compiler** and some standard **C libraries** to run.

### Instructions

**1. Compiling the library**

To compile the library, run:

```shell
$ cd path/to/libft && make
```

**2. Using it in your code**

To use the library functions in your code, simply include its header:

```C
#include "libft.h"
```

and, when compiling your code, add the required flags:

```shell
-lft -L path/to/libft.a -I path/to/libft.h
```
Made with :heart: by <a href="https://github.com/Aelbakouri" target="_blank">Aelbakouri</a>

&#xa0;
<a href="#top">Back to top</a>
