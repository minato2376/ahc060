# Code Style for Competitive Programming

Use the utility functions and macros defined in `library-cpp/other/template.hpp` instead of writing raw equivalents.

## For Loops — `rep` / `rrep`

Use `rep` and `rrep` macros instead of raw `for` loops.

```cpp
rep(n)          // loop n times (no loop variable)
rep(i, n)       // i = 0, 1, ..., n-1
rep(i, l, r)    // i = l, l+1, ..., r-1

rrep(i, n)      // i = n-1, n-2, ..., 0
rrep(i, l, r)   // i = r-1, r-2, ..., l
```

## Output — `print`

Use `print` instead of `cout`.

```cpp
print(args...)   // space-separated output + newline
print(vector)    // space-separated elements + newline
```

## Bit Operations

Use the template-provided bit functions instead of raw bit manipulation.

```cpp
topbit(x)      // position of the most significant bit
botbit(x)      // position of the least significant bit
popcount(x)    // number of set bits
kthbit(x, k)   // value of the k-th bit
popparity(x)   // parity of set bits
```
