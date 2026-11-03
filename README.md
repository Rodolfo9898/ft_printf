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
part, which was not done). The one exception is `%%`: with flags or a width
in between, such as `%5%`, it prints a single `%`, as glibc does. Any other
conversion with flags, such as `%5d`, is printed as is. An unknown specifier
such as `%y` is printed as is,
as glibc does. A `NULL` format, or a format whose last character is a lone `%`
(such as `"abc%"`), makes the call return `-1` **without printing anything**:
the format is checked before the first character is written, so the output is
never left half-done. glibc behaves the same way.

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
| `error` | set when a `write` fails or when `count` would overflow `INT_MAX` |

These three values always travel together, so a struct with named fields is
clearer than separate variables, and one pointer lets `pf_print_segment` read
the position and update the count while staying within the Norm's limit of
four parameters.

**Check first, then one pass over the format.** A `NULL` format returns `-1`
at once, as glibc does. Otherwise `pf_format_is_valid` first scans the format
without printing, skipping each `%` together with the character after it, or
a whole `%%` with flags or a width in between, such as `%5%` (measured by
`pf_flagged_percent_length`). If a `%` is the last character, `ft_printf` returns `-1` before anything is
written. Without this check, `"abc%"` would print `abc` and only then fail,
which differs from glibc and leaves the caller with output it cannot undo. The
check costs one extra pass over the format, which is cheap next to the
`write` calls.

The printing loop then stops at the `'\0'` or as soon as `error` is set.
Each turn, `pf_print_segment` prints one segment and moves `pos` past it: on a
`%`, a single `%` for a flagged `%%` such as `%5%`, or else the conversion
named by the next character; otherwise, all the plain text up to the next `%`
(or the end), in a single `write`. The check and the printing loop skip the
same characters, and because of the check the character after a `%` is never
the `'\0'`, so `pos` cannot move past the end of the format.

**Dispatch** (`ft_dispatch.c`). The specifier goes to
`pf_print_conversion`: an `if` chain
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
  function covers every base. The length is computed once per number. Every
  caller passes one of the fixed digit strings; a base shorter than 2 still
  returns `-1`, since it would divide by zero or never end.
- `number` is a `uintmax_t`, which holds every `unsigned int` and every
  pointer (`uintptr_t`), so no conversion can overflow.
- `pf_putnbr` negates the `int` as an `unsigned int`, where negation is
  defined for every value, so `-INT_MIN` does not overflow whatever the
  size of `long`.
- Digits are produced least significant first, from right to left, into a
  local buffer of `sizeof(uintmax_t) * CHAR_BIT` bytes (64 on usual
  platforms): one byte per bit, which is enough for any `uintmax_t` even in
  base 2. The size is derived from the type rather than hard-coded, so it
  stays correct wherever `uintmax_t` is wider. It is written in the
  declaration rather than as a `#define`, because the Norm only allows
  literal values in a `#define`. The number is then printed with a single
  call to `pf_write_all`. The buffer lives on the stack, so nothing is allocated and nothing
  can leak or fail, and no state is kept from one call to the next.

`%s` with `NULL` prints `(null)`, and `%p` with `NULL` prints `NULL_PTR_STR`:
`(nil)` on Linux and `0x0` on macOS, matching each platform's own `printf`.

**No output buffer.** The subject forbids reimplementing `printf`'s buffer
management, so output goes straight to `write(2)`: one system call per run
of plain text, one per string, and one per number. Plain text needs no buffer,
since it is already contiguous in the format string. `write` may write fewer
bytes than asked (for example when a signal arrives after part of the data was
written to a full pipe), so every printer goes through `pf_write_all`
(`ft_dispatch.c`). It calls `write` again for the rest until the whole buffer
is out, and returns `-1` if `write` fails or writes nothing. A `write`
interrupted before writing anything fails with `EINTR` and is not retried,
because `errno` is not among the subject's authorized functions; `ft_printf`
then returns `-1`, as for any other failed `write`. A buffer longer than
`INT_MAX` returns `-1`, since its length could not be counted. This keeps the
ordering with other `write` calls predictable, and a failed `write` is seen
at once, so `ft_printf` returns `-1` immediately instead of failing later at
flush time.

## Resources

- `man 3 printf`, `man 3 stdarg`
- ISO C11 standard, section 7.16 (variable arguments), on passing a `va_list`
  to another function
- The 42 Norm (`en.norm.pdf`) and the ft_printf subject

**Use of AI.** An AI assistant (Claude) reviewed the finished library against the subject, pointed out failures and explained why they did not match the subject, and proposed fixes.
