# TermClock

A clock in the terminal. Uses the system() function to clear the console as some windows console versions don't support ansi escape codes.

# Features

TermClock takes in the UTC timezone as an argument i.e. If you live in UTC+5 you'd type:

```bash
./termClock 5
```

And the same goes for say UTC-3:
```bash
./termClock -3
```

# How to compile form source

Very simple, very demure:
```bash
gcc src/*.c -Wall -Werror -o termClock
```
