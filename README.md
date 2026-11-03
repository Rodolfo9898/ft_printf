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
as glibc does. A `%` at the very end of the format, or a `NULL` format, makes
the call return `-1`.

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

**State: one small struct.** `ft_printf` (`ft_printf.c`) keeps all of its
state in a `t_state` (`ft_printf.h`) and passes a pointer to it around:

| Field | Meaning |
|---|---|
| `pos` | index of the current character in the format string |
| `count` | number of characters printed so far, i.e. the return value |
| `error` | set when a `write` fails, when `count` would overflow `INT_MAX`, or when the format ends in `%` |

These three values always travel together, so a struct with named fields is
clearer than separate variables, and one pointer lets the dispatcher read the
position and update the count while staying within the Norm's limit of four
parameters.

**One pass over the format.** The loop in `ft_printf` stops at the `'\0'` or
as soon as `error` is set. Ordinary characters are printed straight away. On a
`%`, `pos` moves to the specifier and `pf_dispatch` takes over. The error flag
is tested before the next character is read, so a `%` at the very end can
never make the loop read past the `'\0'`. A `NULL` format returns `-1` at
once, as glibc does.

**Dispatch** (`ft_dispatch.c`). `pf_dispatch` flags a `'\0'` after `%` as an
error and hands every other specifier to `pf_print_conversion`: an `if` chain
with one branch per conversion, each reading its argument with the right type
(`int` for `%c`, `%d` and `%i`, because `char` is promoted to `int` when it is
passed through `...`; `unsigned int` for `%u`, `%x` and `%X`; `char *` for
`%s`; `void *` for `%p`). `%%` has its own branch. Any other character goes to
`pf_print_unknown`, which prints `%` and the character unchanged and consumes
no argument. This chain is the only list of supported specifiers. A table of
function pointers was not used: every conversion reads a different argument
type, so each entry would need its own wrapper, and for nine cases the chain
is shorter and easier to follow.
Every printer returns the number of characters it wrote, or `-1`.
`pf_add_count` adds that number to `count`, or sets `error` if the number is
`-1` or the total would go past `INT_MAX`.

The `va_list` travels down the chain **by pointer**: the C standard leaves a
`va_list` indeterminate in the caller once a callee has used `va_arg` on a
copy, and on arm64 such a copy never advances, so every conversion would read
the first argument again.

**Numbers: one base-conversion routine** (`ft_print_utils.c`).
`pf_putnbr_base(number, base)` prints `%u` (base `DECIMAL`), `%x`
(`HEX_LOWER`), `%X` (`HEX_UPPER`) and the digits of `%p`. `%d`/`%i` go through
`pf_putnbr`, which prints the `-` itself and then hands the magnitude to the
same routine. Choices:
- The base is passed as its digit string, so its length is the radix and one
  function covers every base. The length is computed once per number, and
  a base with fewer than two digits is rejected with `-1`.
- `number` is a `uintmax_t`, which holds every `unsigned int` and every
  pointer (`uintptr_t`), so no conversion can overflow.
- `pf_putnbr` negates the `int` as an `unsigned int`, where negation is
  defined for every value, so `-INT_MIN` does not overflow whatever the
  size of `long`.
- Digits are produced least significant first, from right to left, into a
  local buffer of `MAX_DIGITS` (64) bytes, which is enough for any
  `uintmax_t` even in base 2. The number is then printed with a single
  `write`. The buffer lives on the stack, so nothing is allocated and nothing
  can leak or fail, and no state is kept from one call to the next.

`%s` with `NULL` prints `(null)`, and `%p` with `NULL` prints `NULL_PTR_STR`:
`(nil)` on Linux and `0x0` on macOS, matching each platform's own `printf`.

**No output buffer.** The subject forbids reimplementing `printf`'s buffer
management, so output goes straight to `write(2)`: one system call per plain
character, one per string, and one per number. A string longer than
`INT_MAX` returns `-1`, since its length could not be counted. This keeps the
ordering with other `write` calls predictable, and a failed `write` is seen
at once, so `ft_printf` returns `-1` immediately instead of failing later at
flush time.

## Resources

- `man 3 printf`, `man 3 stdarg`
- ISO C11 standard, section 7.16 (variable arguments), on passing a `va_list`
  to another function
- The 42 Norm (`en.norm.pdf`) and the ft_printf subject

**Use of AI.** An AI assistant (Claude) was used to review the project, to
find the `va_list` portability bug and the missing error handling, to patch
them inside the existing design, and to draft this README. After the
restructuring, it was also used to handle a `NULL` format, to make `%%`
explicit in the dispatch, to print numbers from a local buffer, and to
rewrite the algorithm section above to match the code. All changes were
tested against the system `printf`.
