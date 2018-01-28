# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

a word invented by the president of the National Puzzlers' League as a synonym for the disease known as silicosis.

## According to its man page, what does `getrusage` do?

get resource usage measures.

## Per that same man page, how many members are in a variable of type `struct rusage`?

16 members.

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

we need `calculate` to change the content of `before` and `after` so we need to pass in pointers.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

it reads a character at a time, if it is alphabetical then consider it is a valid character of a word, ignore any numbers, and
characters beyond length of 45. With that iteration we will hit the end of a word, then we can safely pass the word to check.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

with fgetc we can check numbers and non-alphabetical characters more easily.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

make sure the variables always point to the pass-in argument, because we don't need to change them to other addresses.
