# Questions

## What's `stdint.h`?

`stdint.h` is a header file includes some useful typedefs and specify exact-width integer types.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

it makes the size and signing of the data types clear.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

1, 4, 4, 2.

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

0x42 0x4D

## What's the difference between `bfSize` and `biSize`?

`bfSize` is the size of the whole bitmap file while `biSize` is the size of BITMAPINFOHEADER.

## What does it mean if `biHeight` is negative?

the bitmap is a top-down DIB and its origin is the upper-left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

`biBitCount`

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

the file doesn't exist or you don't have the permission

## Why is the third argument to `fread` always `1` in our code?

because we only read it one time

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3

## What does `fseek` do?

set the file position indicator

## What is `SEEK_CUR`?

the current position indicator
