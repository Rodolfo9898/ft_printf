*This project has been created as part of the 42 curriculum by rperez-t.*

# ft_printf

## Description

`ft_printf` is a reimplementation of the C library's `printf`, built as the
static library `libftprintf.a`. It writes to standard output and returns the
number of characters printed, or `-1` on error.

Supported conversions:

| Conversion | Prints |
|---|---|
| `%c` | a single character |
| `%s` | a string (`(null)` for a NULL pointer) |
| `%p` | a pointer in hexadecimal with a `0x` prefix (`(nil)` for NULL) |
| `%d`, `%i` | a signed decimal integer |
| `%u` | an unsigned decimal integer |
| `%x`, `%X` | an unsigned integer in lowercase / uppercase hexadecimal |
| `%%` | a literal percent sign |

Flags, field width and precision are not supported (they belong to the bonus
part, which was not done). An unknown specifier such as `%y` is printed as is,
as glibc does, and a `%` at the very end of the format makes the call return
`-1`.

## Instructions

```sh
make        # builds libftprintf.a
make clean  # removes object files
make fclean # removes object files and the library
make re     # rebuilds from scratch
```

Use it in your own program:

```c
#include "ft_printf.h"

int	main(void)
{
	ft_printf("%s is %d years old, lives at %p\n", "Ada", 36, (void *)0x42);
	return (0);
}
```

```sh
cc -Wall -Wextra -Werror main.c -I. -L. -lftprintf
```

## Algorithm and data structure

**The `send` array: the whole state in three ints.** `ft_printf`
(`ft_printf.c`) keeps its state in one small array that it passes around:

| Slot | Meaning |
|---|---|
| `send[0]` | current position in the format string |
| `send[1]` | number of characters printed so far |
| `send[2]` | error flag: a `write` or `malloc` failed, or the format ends in `%` |

The format is walked once. Ordinary characters are printed immediately. On a
`%`, the position moves to the specifier and the array is handed to
`ft_checker_text`, which updates the count and gives the array back. Passing
one pointer instead of separate variables lets every function in the chain
read the position and update the count without extra parameters. The error flag
is tested before the next character is read, so a `%` at the very end can
never make the loop read past the `'\0'`.

**Dispatch as a chain of three checkers** (`ft_switcher.c`).
Each checker is named after the kind of conversion it looks for:
`ft_checker_text` handles `%c`, `%%` and `%s`, and passes anything else on to
`ft_checker_decimal` (`%d`, `%i`, `%u`), which passes the rest on to
`ft_checker_hex` (`%x`, `%X`, `%p`, then the end of the string or an unknown
specifier). Grouping the conversions by kind keeps each function small and
within the Norm's 25 lines. Every printed amount goes
through `ft_add_count`, which either adds it to `send[1]` or, if it is `-1`,
raises `send[2]`.

The `va_list` travels down the chain **by pointer**: the C standard leaves a
`va_list` indeterminate in the caller once a callee has used `va_arg` on a
copy, and on arm64 such a copy never advances, so every conversion would read
the first argument again.

**No output buffer.** Output goes straight to `write(2)`, not to a buffer.
That keeps the code small and makes ordering with other `write` calls
predictable, at the cost of one system call per plain character. The real
`printf` buffers instead, which is faster but needs flushing logic.

**Numbers.**
- Decimal (`%d`, `%i`, `%u`) goes through `ft_itoa`, which takes a `long` so
  that both `INT_MIN` and `UINT_MAX` fit without overflow. It returns a heap
  string that `ft_putnbr` / `ft_putunbr` free right after printing.
- Hexadecimal (`%x`, `%X`, `%p`) is built by `ft_make_hex` from right to left
  in a static buffer, using a single uppercase digit table: for lowercase, the
  letters `A`–`F` are shifted by 32, which is exactly the distance between
  upper- and lowercase in ASCII. The static buffer means no allocation, so
  nothing can fail or leak. The trade-off is that the result is overwritten
  on the next call, which is fine because it is printed immediately.

## Resources

- `man 3 printf`, `man 3 stdarg`
- ISO C11 standard, section 7.16 (variable arguments), on passing a `va_list`
  to another function
- The 42 Norm (`en.norm.pdf`) and the ft_printf subject

**Use of AI.** An AI assistant (Claude) was used to review the project, to
find the `va_list` portability bug and the missing error handling, to patch
them inside the existing design, and to draft this README. All changes were
tested against the system `printf`.
